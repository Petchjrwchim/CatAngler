#include "Inventory.h"
#include <algorithm>
#include <sstream>
#include "TextureManager.h" 
#include "Input.h"
#include "TextManager.h" 

Inventory::Inventory( int capacity)
    :  capacity(capacity), isVisible(false) {
    for(int i=0; i<capacity; i++) m_items.push_back(NULL);
}

Inventory::~Inventory() {
    for (Item* item : m_items) {
        delete item;
    }
}


void Inventory::addItem(Item* item) {
    // Check if the item already exists in the inventory
    auto it = std::find_if(m_items.begin(), m_items.end(), [item](Item* i) {
        return i != nullptr && i->getName() == item->getName();
        });

    // If the item exists, increase its quantity
    if (it != m_items.end() && (item->getType() != "Weapon" && item->getType() != "Rod")) {
        (*it)->additems(1);
    }
    else {
        // Find the first nullptr in the inventory
        auto nullIt = std::find(m_items.begin(), m_items.end(), nullptr);

        // If a nullptr slot is found, replace it with the new item
        if (nullIt != m_items.end()) {
            *nullIt = item;
        }
        else {
            std::cout << "full" << std::endl;
            // If no nullptr slot is found, push the new item to the back of the inventory
            //m_items.push_back(item);
        }
    }
}

void Inventory::removeItem(Item* item) {
    int count = 0;
    for (Item* i : m_items) {
        //std::cout << i->getName() << ", " << item->getName() << std::endl;
        if (i != nullptr && i->getName() == item->getName()) {
            if (i->getQuantity() <= 1 ) {
                m_items.erase(m_items.begin() + count, m_items.begin() + count + 1);
            }
            if (i->getQuantity() > 1) {
                i->removeitems(1);
            }
        }
        count++;
    }
    for (int i = m_items.size(); i < capacity; i++) m_items.push_back(NULL);
}

void Inventory::toggleVisibility() {
    isVisible = !isVisible;
}

void Inventory::render(int x, int y) {
    if (!isVisible) return;

    int screenWidth;
    SDL_Renderer* renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
    SDL_GetRendererOutputSize(renderer, &screenWidth, nullptr);

    int startX = (screenWidth) / 2 - 320;

    TextureManager::GetInstance()->draw("bag", startX + x, y , 640, 640);

    int slotWidth = 32;
    int slotHeight = 32;
    int padding = 10;

    for (int i = 0; i < capacity; ++i) {
        int newX = x + (i % 5) * (slotWidth + padding) + 300; 
        int newY = y + (i / 5) * (slotHeight + padding) + 260;

        SDL_Rect slotRect = { newX, newY, slotWidth, slotHeight };
        TextureManager::GetInstance()->draw("slot", newX, newY, slotWidth, slotHeight);
    }

    for (int i = 0; i < m_items.size(); ++i) {
        if (m_items[i] != nullptr) {
            int newX = x + (i % 5) * (slotWidth + padding) + 300;
            int newY = y + (i / 5) * (slotHeight + padding) + 260;

            SDL_Rect itemRect = { x, y, slotWidth, slotHeight };
            TextureManager::GetInstance()->draw(m_items[i]->getID(), newX, newY, slotWidth, slotHeight);
            std::stringstream strm;
            strm << m_items[i]->getQuantity();
            TextManager::GetInstance()->renderText(strm.str().c_str(), newX + 23, newY + 20, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 10);
            std::cout << m_items[i]->getID() << std::endl;
        }
       
    }

    if (isDragging && selectedItem) {
        TextureManager::GetInstance()->draw(selectedItem->getID(), dragItemRect.x, dragItemRect.y, dragItemRect.w, dragItemRect.h);
    }

}

void Inventory::renderInventoryBar(int x, int y, int *usingSlot) {
    int screenWidth;
    SDL_Renderer* renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
    SDL_GetRendererOutputSize(renderer, &screenWidth, nullptr);
    int startX = (screenWidth - (INVENTORY_BAR_SLOTS * SLOT_WIDTH + (INVENTORY_BAR_SLOTS - 1) * BAR_PADDING)) / 2 + x;
    int startY = y; 

    Vector2D cam = Camera::GetInstance()->getPosition();
    for (int i = 0; i < INVENTORY_BAR_SLOTS; ++i) {
        int newX = startX + i * (SLOT_WIDTH + BAR_PADDING);
        SDL_Rect slotRect = { newX, startY, SLOT_WIDTH, SLOT_HEIGHT };
        TextureManager::GetInstance()->draw("slot", newX, startY, SLOT_WIDTH, SLOT_HEIGHT);

        int usingX = startX + *usingSlot * (SLOT_WIDTH + BAR_PADDING);
        TextureManager::GetInstance()->draw("usingslot", usingX, startY, SLOT_WIDTH , SLOT_HEIGHT);

        std::stringstream strm;
        strm << i+1;
        TextManager::GetInstance()->renderText(strm.str().c_str(), newX + 7, startY + 3,  "assets/fonts/VCR_OSD_MONO_1.001.ttf", 10);

        Input::GetInstance()->addButton(newX - cam.X, startY - cam.Y, SLOT_WIDTH, SLOT_HEIGHT, "play", [usingSlot,i]() {
            *usingSlot = i;
            }, []() {});

        if (i < m_items.size() && m_items[i] != nullptr) {
            TextureManager::GetInstance()->draw(m_items[i]->getID(), newX, startY, 32, 32, SDL_FLIP_NONE, 2.0);
            std::stringstream strm;
            strm << m_items[i]->getQuantity();
            TextManager::GetInstance()->renderText(strm.str().c_str(), newX + 48, startY + 40, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 15);

            if (m_items[i]->getType() == "Weapon") {

                SDL_Rect maxEnd = { newX - x + 7 , startY - y + 585, 50, 5 };
                SDL_Rect currentEnd = { newX - x + 7, startY - y + 585, floor(m_items[i]->getEndurance() * 50 / m_items[i]->getMaxEndurance()), 5};

                SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 0, 0, 0);
                SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &maxEnd);

                SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 255, 0, 0);
                SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &currentEnd);
            }
        }
    }
}

void Inventory::handleMouseEvent(SDL_Event& e) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    //std::cout << mouseX << mouseY << std::endl;
    if (Input::GetInstance()->getMouseButtonDown(1) && !m_items.empty() && !isDragging) {
        int index = findItemIndexAtPosition(mouseX, mouseY);
        if (index != -1) {
            std::cout << "selecting" << std::endl;
            isDragging = true;
            selectedItem = m_items[index];
            selectedItemIndex = index;
        }
    }
    else if (Input::GetInstance()->getMouseButtonUp(1) && isDragging) {
        int newIndex = findItemIndexAtPosition(mouseX, mouseY);
        if (newIndex != -1 && newIndex != selectedItemIndex) {
            std::cout << "swap" << std::endl;
            swapItems(selectedItemIndex, newIndex);
        }
        isDragging = false;
    }
    Vector2D cam = Camera::GetInstance()->getPosition();
    if (Input::GetInstance()->getMouseButtonDown(1) && selectedItem != NULL) TextureManager::GetInstance()->draw(selectedItem->getID(), cam.X + mouseX - 10, cam.Y + mouseY - 10, 32, 32, SDL_FLIP_NONE);
}

int Inventory::findItemIndexAtPosition(int x, int y) {
    int slotWidth = 32;
    int slotHeight = 32;
    int padding = 10;

    for (int i = 0; i < capacity; ++i) {
        int newX = (i % 5) * (slotWidth + padding) + 300;
        int newY = (i / 5) * (slotHeight + padding) + 260;
        if (x >= newX && x <= newX + slotWidth && y >= newY && y <= newY + slotHeight) {
            return i;
        }
    }

    return -1;
}

void Inventory::swapItems(int firstIndex, int secondIndex) {
    if (firstIndex < 0 || firstIndex >= m_items.size() || secondIndex < 0 || secondIndex >= m_items.size()) {
        return; // Invalid indices
    }
    std::swap(m_items[firstIndex], m_items[secondIndex]);
}

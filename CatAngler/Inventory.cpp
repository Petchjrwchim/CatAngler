#include "Inventory.h"
#include "Inventory.h"
#include <algorithm>
#include <sstream>
#include "TextureManager.h" 
#include "TextManager.h" 

Inventory::Inventory( int capacity)
    :  capacity(capacity), isVisible(false) {
}

Inventory::~Inventory() {
    for (Item* item : m_items) {
        delete item; // Clean up item objects
    }
}


void Inventory::addItem(Item* item) {
    bool found = false;
    for (Item* i : m_items) {
        if (i->getName() == item->getName()) {
            i->additems(item->getQuantity());
            found = true;
            break;
        }
    }
    if (!found) {
        m_items.push_back(item);
    }
}

void Inventory::removeItem(int itemID) {

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

    TextureManager::GetInstance()->draw("bag", (screenWidth) / 2 - 320 + x, y , 640, 640);

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
        }
    }
}

void Inventory::renderInventoryBar(int x, int y, int usingSlot) {
    int screenWidth;
    SDL_Renderer* renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
    SDL_GetRendererOutputSize(renderer, &screenWidth, nullptr);

    int startX = (screenWidth - (INVENTORY_BAR_SLOTS * SLOT_WIDTH + (INVENTORY_BAR_SLOTS - 1) * BAR_PADDING)) / 2 + x;
    int startY = y; 

    for (int i = 0; i < INVENTORY_BAR_SLOTS; ++i) {
        int x = startX + i * (SLOT_WIDTH + BAR_PADDING);
        SDL_Rect slotRect = { x, startY, SLOT_WIDTH, SLOT_HEIGHT };
        TextureManager::GetInstance()->draw("slot", x, startY, SLOT_WIDTH, SLOT_HEIGHT);

        int usingX = startX + usingSlot * (SLOT_WIDTH + BAR_PADDING);
        TextureManager::GetInstance()->draw("usingslot", usingX, startY, SLOT_WIDTH , SLOT_HEIGHT);

        if (i < m_items.size() && m_items[i] != nullptr) {
            TextureManager::GetInstance()->draw(m_items[i]->getID(), x, startY, 32, 32, SDL_FLIP_NONE, 2.0);
            std::stringstream strm;
            strm << m_items[i]->getQuantity();
            TextManager::GetInstance()->renderText(strm.str().c_str(), x + 48, startY + 36, "assets/fonts/PixelifySans.ttf", 20);
        }
    }
}

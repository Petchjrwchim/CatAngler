#include "Inventory.h"
#include "Inventory.h"
#include "TextureManager.h" 

Inventory::Inventory( int capacity)
    :  capacity(capacity), isVisible(false) {
}

Inventory::~Inventory() {
    for (Item* item : m_items) {
        delete item; // Clean up item objects
    }
}


void Inventory::addItem(Item* item) {
    m_items.push_back(item);
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

    std::cout << x << "," << y << std::endl;
    TextureManager::GetInstance()->draw("bag", (screenWidth) / 2 - 320 + x, y , 640, 640);

    int slotWidth = 51;
    int slotHeight = 50;
    int padding = 11;

    for (int i = 0; i < capacity; ++i) {
        int newX = x + (i % 5) * (slotWidth + padding) + 250; 
        int newY = y + (i / 5) * (slotHeight + padding) + 170;

        SDL_Rect slotRect = { newX, newY, slotWidth, slotHeight };
        TextureManager::GetInstance()->draw("slot", newX, newY, slotWidth, slotHeight);
    }

    for (int i = 0; i < m_items.size(); ++i) {
        if (m_items[i] != nullptr) {
            int newX = x + (i % 6) * (slotWidth + padding) + 250;
            int newY = y + (i / 6) * (slotHeight + padding) + 170;

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
        TextureManager::GetInstance()->draw("slot", usingX, startY, SLOT_WIDTH + 10, SLOT_HEIGHT + 10);

        if (i < m_items.size() && m_items[i] != nullptr) {
            TextureManager::GetInstance()->draw(m_items[i]->getID(), x, startY, SLOT_WIDTH, SLOT_HEIGHT);
        }
    }
}

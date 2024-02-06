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

void Inventory::render() {
    if (!isVisible) return;

    SDL_Rect backgroundRect = { 100, 100, 800, 600 }; 
    TextureManager::GetInstance()->draw("background", 100, 100, 800, 600);

    int slotWidth = 64;
    int slotHeight = 64;
    int padding = 10;
    int startX = 150; 
    int startY = 150; 

    for (int i = 0; i < capacity; ++i) {
        int x = startX + (i % 10) * (slotWidth + padding); 
        int y = startY + (i / 10) * (slotHeight + padding);

        SDL_Rect slotRect = { x, y, slotWidth, slotHeight };
        TextureManager::GetInstance()->draw("slot", x, y, 64, 64);
    }

    for (int i = 0; i < m_items.size(); ++i) {
        if (m_items[i] != nullptr) {
            int x = startX + (i % 10) * (slotWidth + padding); 
            int y = startY + (i / 10) * (slotHeight + padding);

            SDL_Rect itemRect = { x, y, slotWidth, slotHeight };
            TextureManager::GetInstance()->draw(m_items[i]->getID(), x, y, 64, 64);
        }
    }
}

void Inventory::renderInventoryBar(int x, int y) {
    int screenWidth;
    SDL_Renderer* renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
    SDL_GetRendererOutputSize(renderer, &screenWidth, nullptr);

    int startX = (screenWidth - (INVENTORY_BAR_SLOTS * SLOT_WIDTH + (INVENTORY_BAR_SLOTS - 1) * BAR_PADDING)) / 2 + x;
    int startY = y; 

    for (int i = 0; i < INVENTORY_BAR_SLOTS; ++i) {
        int x = startX + i * (SLOT_WIDTH + BAR_PADDING);
        SDL_Rect slotRect = { x, startY, SLOT_WIDTH, SLOT_HEIGHT };
        TextureManager::GetInstance()->draw("slot", x, startY, SLOT_WIDTH, SLOT_HEIGHT);

        if (i < m_items.size() && m_items[i] != nullptr) {
            TextureManager::GetInstance()->draw(m_items[i]->getID(), x, startY, SLOT_WIDTH, SLOT_HEIGHT);
        }
    }
}

#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Item.h"
#include "SDL.h"

class Inventory {
private:
    std::vector<Item*> m_items;
    bool isVisible = false;
    int capacity;
    static const int INVENTORY_BAR_SLOTS = 5;
    static const int SLOT_WIDTH = 64;
    static const int SLOT_HEIGHT = 64;
    static const int BAR_PADDING = 10;

public:
    Inventory(int capacity);
    ~Inventory();

    inline std::vector<Item*> getItems() const { return m_items; }
    void addItem(Item* item);
    void removeItem(int itemID);
    void toggleVisibility();
    void render(int x, int y);
    void renderInventoryBar(int x, int y);
    bool checkVisible() { return isVisible; }
};

#endif // INVENTORY_H

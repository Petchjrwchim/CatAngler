#pragma once
#ifndef SHOP_H
#define SHOP_H

#include "SDL.h"
#include <vector>
#include <string>
#include "Item.h"
#include "Input.h" 
#include "Inventory.h"

class Shop {
public:

    Shop(Inventory* inv);
    ~Shop();

    bool get_IsVisible() const { return m_isVisible; }
    int get_Selecting() const { return m_Selecting; }

    void setTab(const std::string& tab) { m_currentTab = tab; }
    void toggleShopUI();    
    void render(SDL_Renderer* renderer);     
    void setSelection(int i) { m_Selecting = i; }
    void update(int x, int y);

private:
    
    int m_X, m_Y;
    int m_Selecting = 0;

    Inventory* m_PlayerInventory;

    std::string m_currentTab = "buy";
    bool m_isVisible;     
    std::vector<Item*> m_items; 
    void initButtons();     
    void renderItems(SDL_Renderer* renderer); 
};

#endif 
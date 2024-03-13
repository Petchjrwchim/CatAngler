#include "Shop.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "Input.h"
#include "FishingRod.h"
#include "Sword.h"
#include "Food.h"

#include <sstream>

static int test = 100;

Shop::Shop() : m_isVisible(false), playerCoin(test) {

    FishingRod* fishingRod = new FishingRod(1, "Fishing Rod", "Rod", "fishingrod", 50);
    Sword* sword = new Sword(1, "Sword", "Weapon", "sword", 50, 100, 1);
    Sword* goldsword = new Sword(1, "Gold Sword", "Weapon", "goldsword", 75, 200, 2);
    Food* fishcan = new Food(1, "Fishcan", "Food", "fishcan", 20, 2);

    m_items.push_back(fishingRod);
    m_items.push_back(sword);
    m_items.push_back(goldsword);
    m_items.push_back(fishcan);

    current_Items = m_items;

    initButtons();
}

Shop::~Shop() {
}

void Shop::toggleShopUI() {
    m_isVisible = !m_isVisible;
}

void Shop::render(SDL_Renderer* renderer) {
    if (!m_isVisible) return;

    int screenWidth;
    renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
    SDL_GetRendererOutputSize(renderer, &screenWidth, nullptr);

    if (m_currentTab == "sell") {
        TextureManager::GetInstance()->draw("sell_tab", screenWidth / 2 - 400 + m_X, m_Y, 800, 600);
    }
    else if (m_currentTab == "buy") {
        TextureManager::GetInstance()->draw("buy_tab", screenWidth / 2 - 400 + m_X, m_Y, 800, 600);
    }

    TextManager::GetInstance()->renderText("Buy", screenWidth / 2 - 170 + m_X, m_Y + 90, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 30);
    TextManager::GetInstance()->renderText("Sell", screenWidth / 2 + 120 + m_X, m_Y + 90, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 30);

    renderItems(renderer);

    //Input::GetInstance()->renderButtons(renderer);
}

void Shop::update(int x, int y) {
    if (m_isVisible) {
        Input::GetInstance()->setCurrentWindow("shop");
        m_X = x;
        m_Y = y;
    }
    else {
        Input::GetInstance()->setCurrentWindow("play");
    }
}

void Shop::addMultipleButton(std::vector<Item*> items) {
    int slotWidth = 64;
    int slotHeight = 64;
    int padding = 10;

    for (int i = 0; i <  items.size(); ++i) {
        int newX = (i % 4) * (slotWidth + padding) + 120;
        int newY = (i / 4) * (slotHeight + padding) + 160;

        Input::GetInstance()->addButton(newX, newY, slotWidth, slotHeight, "shop", [this, i]() {
            this->setSelection(i);
            }, []() {});
    }
}

void Shop::initButtons() {

    Input::GetInstance()->addButton( m_X + 405, m_Y + 80, 295, 50, "shop", [this]() {
        this->setTab("sell");
        current_Items = m_PlayerInventory->getItems();
        std::cout << "Sell tab clicked" << std::endl;
        Input::GetInstance()->deleteButton(46); // delete excess button
        addMultipleButton(current_Items);
        }, []() {});

    Input::GetInstance()->addButton( m_X + 105, m_Y + 80 , 295, 50, "shop", [this]() {
        this->setTab("buy");
        current_Items = m_items;
        std::cout << "Buy tab clicked" << std::endl;
        Input::GetInstance()->deleteButton(46); // delete excess button
        addMultipleButton(current_Items);

        }, []() {});

    Input::GetInstance()->addButton(m_X + 568, m_Y + 437, 98, 54, "shop", [this]() {
        if (get_CurrentTab() == "buy" && !current_Items.empty() && current_Items.size() + 1 <= 10) {
            Item* selectedItem = current_Items[this->get_Selecting()];
            int itemPrice = selectedItem->getPrice();
            if (playerCoin - itemPrice >= 0) {
                std::cout << "Buy" << std::endl;
                playerCoin -= itemPrice;
                Item* ni = selectedItem->clone();
                ni->setEndurance(ni->getMaxEndurance());
                m_PlayerInventory->addItem(ni); // Add a clone of the item
            }
        }
        else if (get_CurrentTab() == "sell" && !current_Items.empty() && m_Selecting < current_Items.size()) {
            Item* selectedItem = current_Items[this->get_Selecting()];
            int sellPrice = ceil(selectedItem->getPrice() * 0.6);
            std::cout << "Sell" << std::endl;
            playerCoin += sellPrice;
            m_PlayerInventory->removeItem(selectedItem);
            // You might also need to delete the item if it's no longer needed
        }
        }, []() {});

    addMultipleButton(current_Items);
}

void Shop::renderItems(SDL_Renderer* renderer) {

    int slotWidth = 32;
    int slotHeight = 32;
    int padding = 40;

    if (m_currentTab == "sell") current_Items = m_PlayerInventory->getItems();
    if (m_currentTab == "buy") current_Items = m_items;;

    for (int i = 0; i < current_Items.size(); ++i) {
        int newX = m_X + (i % 4) * (slotWidth + padding) + 120;
        int newY = m_Y + (i / 4) * (slotHeight + padding) + 160;

        TextureManager::GetInstance()->draw("slot", newX, newY, slotWidth, slotHeight, SDL_FLIP_NONE, 2.0);

    }

    if (!current_Items.empty() && m_Selecting < current_Items.size() && current_Items[m_Selecting] != NULL) {
        int selectingX = m_X + (m_Selecting % 4) * (slotWidth + padding) + 120;
        int selectingY = m_Y + (m_Selecting / 4) * (slotHeight + padding) + 160;
        TextureManager::GetInstance()->draw("usingslot", selectingX, selectingY, slotWidth, slotHeight, SDL_FLIP_NONE, 2.0);

        TextureManager::GetInstance()->draw("slot", m_X + 480, m_Y + 150, slotWidth, slotHeight, SDL_FLIP_NONE, 4.0);
        TextureManager::GetInstance()->draw(current_Items[m_Selecting]->getID(), m_X + 480, m_Y + 150, slotWidth, slotHeight, SDL_FLIP_NONE, 4.0);

        TextManager::GetInstance()->renderText("Description: ", m_X + 450, m_Y + 300, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 20);
        TextManager::GetInstance()->renderText(current_Items[m_Selecting]->getDescription().c_str(), m_X + 450, m_Y + 320, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 20);

        TextureManager::GetInstance()->draw("button", m_X + 550, m_Y + 400, 64, 64, SDL_FLIP_NONE, 2.0);
        TextureManager::GetInstance()->draw("coin", m_X + 560, m_Y + 435, 32, 32, SDL_FLIP_NONE, 2.0);
        std::stringstream strm;
        if (get_CurrentTab() == "buy") strm << current_Items[m_Selecting]->getPrice();
        if (get_CurrentTab() == "sell") strm << ceil(current_Items[m_Selecting]->getPrice() * 0.6);
        TextManager::GetInstance()->renderText(strm.str().c_str(), m_X + 620, m_Y + 452, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 20);
    }
    else {

    }


    for (int i = 0; i < current_Items.size(); ++i) {
        if (current_Items[i] != nullptr) {
            int newX = m_X + (i % 4) * (slotWidth + padding) + 120;
            int newY = m_Y + (i / 4) * (slotHeight + padding) + 160;
            TextureManager::GetInstance()->draw(current_Items[i]->getID(), newX, newY, slotWidth, slotHeight, SDL_FLIP_NONE, 2.0);

            if (m_currentTab == "sell") {
                std::stringstream strm;
                strm << current_Items[i]->getQuantity();
                TextManager::GetInstance()->renderText(strm.str().c_str(), newX + 48, newY + 36, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 20);
            }
        }
    }
}


//int slotWidth = 64;
//int slotHeight = 64;
//int padding = 10;
//
//for (int i = 0; i < m_items.size(); ++i) {
//    int newX = m_X + (i % 4) * (slotWidth + padding) + 120;
//    int newY = m_Y + (i / 4) * (slotHeight + padding) + 160;
//
//
//    Input::GetInstance()->addButton(newX, newY, slotWidth, slotHeight, [this, i]() {
//        this->setSelection(i);
//        });
//}
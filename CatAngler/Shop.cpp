#include "Shop.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "Input.h"
#include "FishingRod.h"
#include "Sword.h"

Shop::Shop(Inventory* inv, int& coin) : m_PlayerInventory(inv), playerCoin(coin), m_isVisible(false) {
    
    FishingRod* fishingRod = new FishingRod(1, "Fishing Rod", "Rod", "fishingrod", 50);
    Sword* sword = new Sword(1, "Sword", "Weapon", "sword", 50);

    m_items.push_back(fishingRod);
    m_items.push_back(sword);

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

    TextureManager::GetInstance()->draw("slot", m_X + 600, m_Y + 400, 32, 32, SDL_FLIP_NONE, 2.0);

    TextManager::GetInstance()->renderText("Buy", screenWidth / 2 - 170 + m_X, m_Y + 90, "assets/fonts/PixelifySans.ttf", 30);
    TextManager::GetInstance()->renderText("Sell", screenWidth / 2 + 120 + m_X, m_Y + 90, "assets/fonts/PixelifySans.ttf", 30);

    renderItems(renderer);

    Input::GetInstance()->renderButtons(renderer);
}

void Shop::update(int x, int y) {
    if (m_isVisible) {
        m_X = x;
        m_Y = y;
        Input::GetInstance()->handleButtonEvents();
    }
}

void Shop::initButtons() {

    Input::GetInstance()->addButton( m_X + 405, m_Y + 80, 295, 50, [this]() {
        this->setTab("sell");
        current_Items = m_PlayerInventory->getItems();
        std::cout << "Sell tab clicked" << std::endl;
        });

    Input::GetInstance()->addButton( m_X + 105, m_Y + 80 , 295, 50, [this]() {
        this->setTab("buy");
        current_Items = m_items;
        std::cout << "Buy tab clicked" << std::endl;
        });

    Input::GetInstance()->addButton(m_X + 600, m_Y + 400, 64, 64, [this]() {
        if (get_CurrentTab() == "buy") {
            std::cout << "Buy" << std::endl;
            playerCoin -= m_items[this->get_Selecting()]->getPrice();
            m_PlayerInventory->addItem(m_items[this->get_Selecting()]);
        }
        else if (get_CurrentTab() == "sell") {
            std::cout << "Sell" << std::endl;
            playerCoin += m_items[this->get_Selecting()]->getPrice() * 0.6;
            m_PlayerInventory->removeItem(m_PlayerInventory->getItems()[this->get_Selecting()]);
        }
        });
    std::cout << m_X << ", " << m_Y << std::endl;
}

void Shop::renderItems(SDL_Renderer* renderer) {

    std::cout << m_X << ", " << m_Y << std::endl;

    int slotWidth = 32;
    int slotHeight = 32;
    int padding = 40;

    for (int i = 0; i < current_Items.size(); ++i) {
        int newX = m_X + (i % 4) * (slotWidth + padding) + 120;
        int newY = m_Y + (i / 4) * (slotHeight + padding) + 160;

        TextureManager::GetInstance()->draw("slot", newX, newY, slotWidth, slotHeight, SDL_FLIP_NONE, 2.0);
    }

    int selectingX = m_X + (m_Selecting % 4) * (slotWidth + padding) + 120;
    int selectingY = m_Y + (m_Selecting / 4) * (slotHeight + padding) + 160;
    TextureManager::GetInstance()->draw("usingslot", selectingX, selectingY, slotWidth, slotHeight, SDL_FLIP_NONE, 2.0);

    for (int i = 0; i < current_Items.size(); ++i) {
        if (current_Items[i] != nullptr) {
            int newX = m_X + (i % 4) * (slotWidth + padding) + 120;
            int newY = m_Y + (i / 4) * (slotHeight + padding) + 160;
            TextureManager::GetInstance()->draw(current_Items[i]->getID(), newX, newY, slotWidth, slotHeight, SDL_FLIP_NONE, 2.0);
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
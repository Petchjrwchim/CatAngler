#include "Shop.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "Input.h"
#include "FishingRod.h"
#include "Sword.h"

Shop::Shop(Inventory* inv) : m_PlayerInventory(inv), m_isVisible(false) {
    initButtons();
    FishingRod* fishingRod = new FishingRod(1, "Fishing Rod", "Rod", "fishingrod");
    Sword* sword = new Sword(1, "Sword", "Weapon", "sword");

    m_items.push_back(fishingRod);
    m_items.push_back(sword);
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
        TextureManager::GetInstance()->draw("slot", m_X + 600, m_Y + 400, 32, 32, SDL_FLIP_NONE, 2.0);
    }

    TextManager::GetInstance()->renderText("Buy", screenWidth / 2 - 170 + m_X, m_Y + 90, "assets/fonts/PixelifySans.ttf", 30);
    TextManager::GetInstance()->renderText("Sell", screenWidth / 2 + 120 + m_X, m_Y + 90, "assets/fonts/PixelifySans.ttf", 30);

    //buy button
    

    renderItems(renderer);

    //Input::GetInstance()->renderButtons(renderer);
}

void Shop::update(int x, int y) {
    m_X = x;
    m_Y = y;
    Input::GetInstance()->handleButtonEvents();
}

void Shop::initButtons() {

    Input::GetInstance()->addButton( m_X + 405, m_Y + 80, 295, 50, [this]() {
        this->setTab("sell");
        std::cout << "Sell tab clicked" << std::endl;
        });

    Input::GetInstance()->addButton( m_X + 105, m_Y + 80 , 295, 50, [this]() {
        this->setTab("buy");
        std::cout << "Buy tab clicked" << std::endl;
        });

    Input::GetInstance()->addButton(m_X + 600, m_Y + 400, 64, 64, [this]() {
        std::cout << "Buy" << std::endl;
        m_PlayerInventory->addItem(m_items[this->get_Selecting()]);
        });


    int capacity = 10;
    int slotWidth = 64;
    int slotHeight = 64;
    int padding = 10;

    for (int i = 0; i < capacity; ++i) {
        int newX = m_X + (i % 4) * (slotWidth + padding) + 120;
        int newY = m_Y + (i / 4) * (slotHeight + padding) + 160;

        SDL_Rect slotRect = { newX, newY, slotWidth, slotHeight };
        TextureManager::GetInstance()->draw("slot", newX, newY, slotWidth, slotHeight, SDL_FLIP_NONE, 2.0);

        Input::GetInstance()->addButton(newX, newY, slotWidth, slotHeight, [this, i]() {
            this->setSelection(i);
            });
    }
}

void Shop::renderItems(SDL_Renderer* renderer) {
    int capacity = 10;
    int slotWidth = 32;
    int slotHeight = 32;
    int padding = 40;

    if (m_currentTab == "buy") {
        for (int i = 0; i < capacity; ++i) {
            int newX = m_X + (i % 4) * (slotWidth + padding) + 120;
            int newY = m_Y + (i / 4) * (slotHeight + padding) + 160;

            TextureManager::GetInstance()->draw("slot", newX, newY, slotWidth, slotHeight, SDL_FLIP_NONE, 2.0);
        }

        int selectingX = m_X + (m_Selecting % 4) * (slotWidth + padding) + 120;
        int selectingY = m_Y + (m_Selecting / 4) * (slotHeight + padding) + 160;
        TextureManager::GetInstance()->draw("usingslot", selectingX, selectingY, slotWidth, slotHeight, SDL_FLIP_NONE, 2.0);

        for (int i = 0; i < m_items.size(); ++i) {
            if (m_items[i] != nullptr) {
                int newX = m_X + (i % 4) * (slotWidth + padding) + 120;
                int newY = m_Y + (i / 4) * (slotHeight + padding) + 160;

                TextureManager::GetInstance()->draw(m_items[i]->getID(), newX, newY, slotWidth, slotHeight, SDL_FLIP_NONE, 2.0);
            }
        }
    }

}
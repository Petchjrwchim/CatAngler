#include "Menu.h"
#include "Engine.h"
#include "TextManager.h"
#include "TextureManager.h"

Menu::Menu()
{
    m_Aimation = new Animation();
    m_Aimation->setProps("wallpaper", 1, 2, 1000);
}

bool Menu::init()
{
    m_Ctxt = Engine::GetInstance()->GetRenderer();
    initButtons();
    std::cout << "menu initialized" << std::endl;
    return true;
}

bool Menu::exit()
{
    std::cout << "exit menu" << std::endl;
    return true;
}

void Menu::update()
{
}

void Menu::render()
{
    m_Aimation->draw(16, 115, 800, 600);
    m_Aimation->setProps("wallpaper", 1, 2, 1000);
    m_Aimation->update();


    TextureManager::GetInstance()->draw("badge", 314, 268, 64, 64, SDL_FLIP_NONE, 3);
    TextureManager::GetInstance()->draw("badge", 314, 368, 64, 64, SDL_FLIP_NONE, 3);
    TextureManager::GetInstance()->draw("badge", 314, 468, 64, 64, SDL_FLIP_NONE, 3);

    TextManager::GetInstance()->renderText("Start", 380, 344, "assets/fonts/PixelifySans.ttf", 30);
    TextManager::GetInstance()->renderText("Settings", 350, 444, "assets/fonts/PixelifySans.ttf", 30);
    TextManager::GetInstance()->renderText("Exit", 400, 544, "assets/fonts/PixelifySans.ttf", 30);

    //Input::GetInstance()->renderButtons(m_Ctxt);

}

void Menu::startGame()
{
    Engine::GetInstance()->changeGameState("play");
}

void Menu::settings()
{
}

void Menu::quit()
{
    Engine::GetInstance()->clean();
    Engine::GetInstance()->quit();
}

void Menu::initButtons()
{

    Input::GetInstance()->addButton( 300, 220, 200, 50, "menu", [this]() {
        startGame();
        });

    Input::GetInstance()->addButton( 300, 320, 200, 50, "menu", [this]() {
        });

    Input::GetInstance()->addButton(300, 420, 200, 50, "menu", [this]() {
        quit();
        });
}

void Menu::setCursor(const char* imagePath)
{
    SDL_Surface* cursorSurface = IMG_Load(imagePath);
    if (!cursorSurface) {
        std::cerr << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
        return;
    }

    cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
    if (!cursor) {
        SDL_FreeSurface(cursorSurface);
        std::cerr << "Unable to create color cursor! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_SetCursor(cursor);
    SDL_FreeSurface(cursorSurface);
}

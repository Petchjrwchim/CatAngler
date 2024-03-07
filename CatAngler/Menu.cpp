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
    Vector2D cam = Camera::GetInstance()->getPosition();

    m_Aimation->draw(cam.X, cam.Y, 800, 600);
    m_Aimation->setProps("wallpaper", 1, 2, 1000);
    m_Aimation->update();


    TextureManager::GetInstance()->draw("badge", 314 + cam.X, 148 + cam.Y, 64, 64, SDL_FLIP_NONE, 3);
    TextureManager::GetInstance()->draw("badge", 314 + cam.X, 248 + cam.Y, 64, 64, SDL_FLIP_NONE, 3);
    TextureManager::GetInstance()->draw("badge", 314 + cam.X, 348 + cam.Y, 64, 64, SDL_FLIP_NONE, 3);

    TextManager::GetInstance()->renderText("Start", 380 + cam.X, 224 + cam.Y, "assets/fonts/PixelifySans.ttf", 30);
    TextManager::GetInstance()->renderText("Settings", 350 + cam.X, 324 + cam.Y, "assets/fonts/PixelifySans.ttf", 30);
    TextManager::GetInstance()->renderText("Exit", 400 + cam.X, 424 + cam.Y, "assets/fonts/PixelifySans.ttf", 30);

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
        std::cout << "start" << std::endl;
        startGame();
        });

    Input::GetInstance()->addButton( 300, 320, 200, 50, "menu", [this]() {
        });

    Input::GetInstance()->addButton(300, 420, 200, 50, "menu", [this]() {
        std::cout << "quit game" << std::endl;
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

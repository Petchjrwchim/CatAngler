#include "Menu.h"
#include "Engine.h"


Menu::Menu()
{
}

bool Menu::init()
{
    m_Ctxt = Engine::GetInstance()->GetRenderer();
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
    SDL_SetRenderDrawColor(m_Ctxt, 255, 255, 255, 255);
    SDL_RenderClear(m_Ctxt);

    SDL_RenderPresent(m_Ctxt);
}

void Menu::startGame()
{
}

void Menu::settings()
{
}

void Menu::quit()
{
}

void Menu::initButtons()
{
    Input::GetInstance()->addButton(405, 80, 295, 50, [this]() {

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

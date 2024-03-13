#include "Menu.h"
#include "Engine.h"
#include "TextManager.h"
#include <filesystem>
#include "SaveManager.h"
#include "TextureManager.h"
#include "SoundManager.h"

Menu* Menu::s_Instance = nullptr;

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
    Engine::GetInstance()->setPlayerSlot("");
    IsSelecting = "";
}

void Menu::render()
{
    Vector2D cam = Camera::GetInstance()->getPosition();

    m_Aimation->draw(cam.X, cam.Y, 800, 600);
    m_Aimation->setProps("wallpaper", 1, 2, 1000);
    m_Aimation->update();

    if (currentTab == "menu") {
        Input::GetInstance()->setCurrentWindow("menu"); 
        TextureManager::GetInstance()->draw("logo", 164 + cam.X, cam.Y, 256, 128, SDL_FLIP_NONE, 2);
        TextureManager::GetInstance()->draw("badge", 314 + cam.X, 178 + cam.Y, 64, 64, SDL_FLIP_NONE, 3);
        TextureManager::GetInstance()->draw("badge", 314 + cam.X, 278 + cam.Y, 64, 64, SDL_FLIP_NONE, 3);
        TextureManager::GetInstance()->draw("badge", 314 + cam.X, 378 + cam.Y, 64, 64, SDL_FLIP_NONE, 3);

        TextManager::GetInstance()->renderText("Start", 390 + cam.X, 260 + cam.Y, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 25);
        TextManager::GetInstance()->renderText("Settings", 360 + cam.X, 360 + cam.Y, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 25);
        TextManager::GetInstance()->renderText("Exit", 400 + cam.X, 460 + cam.Y, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 25);

        renderSelected(cam);
    }


    if (currentTab == "save") {
        Input::GetInstance()->setCurrentWindow("save");
        renderSaveScreen(cam);
    }

    if (currentTab == "settings") {
        Input::GetInstance()->setCurrentWindow("settings");
        renderSettings(cam);
    }

    //Input::GetInstance()->renderButtons(m_Ctxt);

}

void Menu::renderSaveScreen(Vector2D cam)
{   

    TextureManager::GetInstance()->draw("exit_button", cam.X + 100, cam.Y, 32, 32, SDL_FLIP_NONE, 2);
    TextureManager::GetInstance()->draw("longslot", 104 + cam.X, 120 + cam.Y, 64, 128, SDL_FLIP_NONE, 3);
    TextureManager::GetInstance()->draw("longslot", 304 + cam.X, 120 + cam.Y, 64, 128, SDL_FLIP_NONE, 3);
    TextureManager::GetInstance()->draw("longslot", 504 + cam.X, 120 + cam.Y, 64, 128, SDL_FLIP_NONE, 3);

    for (int i = 1; i <= 3; i++) {
        std::unordered_map<std::string, int> loadedData = SaveManager::GetInstance()->loadGame("savegame" + std::to_string(i) + ".txt");
        TextureManager::GetInstance()->draw("button", 230 + 200 * (i - 1) + cam.X, 510 + cam.Y, 64, 64, SDL_FLIP_NONE, 2);
        std::string filename = "savegame" + std::to_string(i) + ".txt";
        Input::GetInstance()->addButton(230 + 200 * (i - 1) + cam.X, 510 + cam.Y, 64, 64, "save", [this, filename]() {
            std::cout << "delete slot1" << std::endl;
            std::filesystem::remove(filename);
            }, []() {});
        if (loadedData["Health"] == NULL || loadedData["Health"] <= 0) {
            TextManager::GetInstance()->renderText("Empty", 125 + 200 * (i-1) + cam.X, 300 + cam.Y, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 50);
        }
        else {
            std::string health = "Health : " + std::to_string(loadedData["Health"]);
            std::string coin = "Coin : " + std::to_string(loadedData["Coin"]);
            std::string day = "Day : " + std::to_string(loadedData["Day"]);
            TextManager::GetInstance()->renderText(day.c_str(), 125 + 200 * (i - 1) + cam.X, 280 + cam.Y, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 20);
            TextManager::GetInstance()->renderText(health.c_str(), 125 + 200 * (i - 1) + cam.X, 300 + cam.Y, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 20);
            TextManager::GetInstance()->renderText(coin.c_str(), 125 + 200 * (i - 1) + cam.X, 320 + cam.Y, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 20);
        }
    }
    //Input::GetInstance()->renderButtons(Engine::GetInstance()->GetRenderer());
}

void Menu::renderSettings(Vector2D cam)
{
    TextureManager::GetInstance()->draw("exit_button", cam.X + 100, cam.Y, 32, 32, SDL_FLIP_NONE, 2);
    TextureManager::GetInstance()->draw("tab", 208 + cam.X, 120 + cam.Y, 128, 128, SDL_FLIP_NONE, 3);
    TextManager::GetInstance()->renderText("Background music", 300 + cam.X, 200 + cam.Y, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 20);
    Input::GetInstance()->renderSliders();
    SoundManager::GetInstance()->setMusicVolume( "bgmusic", Input::GetInstance()->getSliderValue(0));
}

void Menu::renderSelected(Vector2D cam)
{
    if (IsSelecting == "start") {
        TextureManager::GetInstance()->draw("arrow", 350 + cam.X, 242 + cam.Y, 64, 64, SDL_FLIP_NONE);
    }
    if (IsSelecting == "settings") {
        TextureManager::GetInstance()->draw("arrow", 320 + cam.X, 342 + cam.Y, 64, 64, SDL_FLIP_NONE);
    }
    if (IsSelecting == "exit") {
        TextureManager::GetInstance()->draw("arrow", 360 + cam.X, 442 + cam.Y, 64, 64, SDL_FLIP_NONE);
    }
}

void Menu::startGame()
{
    Engine::GetInstance()->changeGameState("prepare");
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

    Vector2D cam = Camera::GetInstance()->getPosition();

    Input::GetInstance()->addSlider(250, 230, Engine::GetInstance()->GetRenderer());

    Input::GetInstance()->addButton( 300, 250, 200, 50, "menu", [this]() {
        std::cout << "start" << std::endl;
        //startGame();
        this->currentTab = "save";
    }, [this]() {
        this->IsSelecting = "start";
    });

    Input::GetInstance()->addButton( 300, 350, 200, 50, "menu", [this]() {
        this->currentTab = "settings";
        }, [this]() {
            this->IsSelecting = "settings";
        });

    Input::GetInstance()->addButton(cam.X + 104, cam.Y + 10, 54, 40, "settings", [this]() {
        std::cout << "Exit settings" << std::endl;
        this->currentTab = "menu";
        }, []() {});

    Input::GetInstance()->addButton(300, 450, 200, 50, "menu", [this]() {
        std::cout << "quit game" << std::endl;
        quit();
        }, [this]() {
            this->IsSelecting = "exit";
        });

    Input::GetInstance()->addButton(cam.X + 104, cam.Y + 10, 54, 40, "save", [this]() {
        std::cout << "Exit save" << std::endl;
        this->currentTab = "menu";
        }, []() {});

    Input::GetInstance()->addButton(104 + cam.X, 120 + cam.Y, 192, 384, "save", [this]() {
        std::cout << "slot1" << std::endl;
        Engine::GetInstance()->setPlayerSlot("1");
        startGame();
        this->currentTab = "menu";
        }, []() {});

    Input::GetInstance()->addButton(cam.X + 304, cam.Y + 120, 192, 384, "save", [this]() {
        std::cout << "slot2" << std::endl;
        Engine::GetInstance()->setPlayerSlot("2");
        startGame();
        this->currentTab = "menu";
        }, []() {});

    Input::GetInstance()->addButton(cam.X + 504, cam.Y + 120, 192, 384, "save", [this]() {
        std::cout << "slot3" << std::endl;
        Engine::GetInstance()->setPlayerSlot("3");
        startGame();
        this->currentTab = "menu";
        }, []() {});

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

#include <iostream>

#include "Engine.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"
#include "Cat.h"
#include "Camera.h"
#include "Tile.h"
#include "Shop.h"
#include "Menu.h"

Engine* Engine::s_Instance = nullptr;
Cat* cat = nullptr;
Shop* shop = nullptr;
Tile* m_Tile;
Menu* menu;

bool Engine::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );

	m_Window = SDL_CreateWindow("SDL2 Basic Game",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH,
	SCREEN_HEIGHT,
    window_flags);
	if (m_Window == nullptr) {
		SDL_Log("Failed to create Window: %s", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
	if (m_Renderer == nullptr) {
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
		return false;
	}

	m_Tile = Tile::GetInstance(); // This should assign to the class member
	if (!m_Tile->load("yourMapID", "assets/images/map2.json")) {
		std::cerr << "Failed to load the map." << std::endl;
		return false;
	}

	if (TTF_Init() == -1)
	{
		std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
		return false;
	}


	TextureManager::GetInstance()->parseTexture("assets/images/textures.txt");
	
	menu = new Menu();
	menu->init();

	int tilesize = 32;
	int width = 40 * tilesize;
	int height = 30 * tilesize;

	Camera::GetInstance()->setSceneLimit(width, height);
	cat = new Cat(new Properties("cat", 400 , 400, 32, 32));
	Camera::GetInstance()->setTarget(cat->getOrigin());
	shop = new Shop(cat->getInventory(), cat->getCoin());

	return m_IsRunning = true;
}

bool Engine::clean()
{	
	delete shop;
	shop = nullptr;
	TextureManager::GetInstance()->clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	return true;
}

void Engine::quit()
{
	m_IsRunning = false;
}

void Engine::update()
{

	Vector2D cam = Camera::GetInstance()->getPosition();
	float dt = Timer::GetInstance()->getDeltaTime();

	cat->update(dt);
	
	if (cat->getIs_Shopping() && !shop->get_IsVisible()) {
		shop->toggleShopUI();
	}
	else if (!cat->getIs_Shopping() && shop->get_IsVisible()) {
		shop->toggleShopUI();
	}

	shop->update(cam.X, cam.Y);

	Input::GetInstance()->handleButtonEvents();
	Camera::GetInstance()->update(dt);
}

void Engine::render()
{
	//SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_Renderer);

	if (m_GameState == "menu") menu->render();

	if (m_GameState == "play") {
		if (!cat->getInteract()) {
			m_Tile->render("Floor");
			m_Tile->render("House");
		}
		else {
			m_Tile->render("Indoor");
			m_Tile->render("Shop");
		}

		cat->draw();
		cat->equip();

		if (!cat->getInteract()) {
			m_Tile->render("Tree");
		}
		else {
			TextureManager::GetInstance()->draw("shopkeeper", 445, 520, 36, 36);
			m_Tile->render("Shopkeeper");
		}

		if (shop->get_IsVisible()) {
			shop->render(m_Renderer);
		}

		cat->drawInv();
	}
 
	SDL_RenderPresent(m_Renderer);
}

void Engine::toggleFullscreen() {
	m_IsFullscreen = !m_IsFullscreen;
	if (m_IsFullscreen) {
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
	}
	else {
		SDL_SetWindowFullscreen(m_Window, 0);
	}
}

void Engine::event() {
	SDL_Event event;
	Input::GetInstance()->listen(); // Existing input handling
	if (Input::GetInstance()->getKeyDownOnetime(SDL_SCANCODE_V)) {
		toggleFullscreen();
	}
}



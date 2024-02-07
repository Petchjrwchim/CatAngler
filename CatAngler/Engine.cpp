#include <iostream>

#include "Engine.h"
#include "TextureManager.h"
#include "FishingManager.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"
#include "Cat.h"
#include "Camera.h"
#include "Tile.h"

Engine* Engine::s_Instance = nullptr;
Cat* cat = nullptr;
Tile* m_Tile;

void addFishingRodToCatInventory(Cat* cat) {

	int id = 1; 
	std::string name = "Fishing Rod";
	std::string type = "Rod";
	std::string texture = "fishingrod";
	FishingRod* fishingRod = new FishingRod(id, name, type, texture);

	cat->getInventory()->addItem(fishingRod);
}

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
	if (!m_Tile->load("yourMapID", "assets/images/map.json")) {
		std::cerr << "Failed to load the map." << std::endl;
		return false;
	}

	TextureManager::GetInstance()->parseTexture("assets/images/textures.txt");

	int tilesize = 32;
	int width = 40 * tilesize;
	int height = 30 * tilesize;

	Camera::GetInstance()->setSceneLimit(width, height);

	cat = new Cat(new Properties("cat", 200 , 200, 32, 32));
	Camera::GetInstance()->setTarget(cat->getOrigin());
	addFishingRodToCatInventory(cat);
	

	return m_IsRunning = true;
}

bool Engine::clean()
{	
	TextureManager::GetInstance()->clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
	return true;
}

void Engine::quit()
{
	m_IsRunning = false;
}

void Engine::update()
{

	float dt = Timer::GetInstance()->getDeltaTime();

	cat->update(dt);

	Camera::GetInstance()->update(dt);
}

void Engine::render()
{
	SDL_RenderClear(m_Renderer);

	m_Tile->render("Tile Layer 1");
	cat->draw();
	cat->equip();
	//FishingManager::GetInstance()->update(cat->getFishing(), cat->getX(), cat->getY());
	m_Tile->render("tree");
	cat->drawInv();

	SDL_RenderPresent(m_Renderer);
}

void Engine::toggleFullscreen() {
	m_IsFullscreen = !m_IsFullscreen; // Toggle the fullscreen state
	if (m_IsFullscreen) {
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN); // Set to fullscreen
	}
	else {
		SDL_SetWindowFullscreen(m_Window, 0); // Set to windowed mode
	}
}

void Engine::event() {
	SDL_Event event;
	Input::GetInstance()->listen(); // Existing input handling
	if (Input::GetInstance()->getKeyDownOnetime(SDL_SCANCODE_V)) {
		toggleFullscreen();
	}
}



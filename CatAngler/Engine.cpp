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

bool Engine::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	m_Window = SDL_CreateWindow("SDL2 Basic Game",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
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

	cat = new Cat(new Properties("cat", 200 , 200, 32, 32));
	
	Camera::GetInstance()->setTarget(cat->getOrigin());
	

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
	FishingManager::GetInstance()->update(cat->getFishing(), cat->getX(), cat->getY());
	m_Tile->render("tree");

	SDL_RenderPresent(m_Renderer);
}

void Engine::event()
{
	Input::GetInstance()->listen();
}



#include "Engine.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"
#include <iostream>

#include "Cat.h"

Engine* Engine::s_Instance = nullptr;
Cat* player = nullptr;

bool Engine::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	m_Window = SDL_CreateWindow("SDL2 Basic Game",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH,
	SCREEN_HEIGHT,
    0);
	if (m_Window == nullptr) {
		SDL_Log("Failed to create Window: %s", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
	if (m_Renderer == nullptr) {
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
		return false;
	}

	TextureManager::GetInstance()->load("player_run", "assets\\images\\cat.png");
	TextureManager::GetInstance()->load("player", "assets\\images\\cat_idle.png");

	player = new Cat(new Properties("player", SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2, 32, 32));

	Transform tf;

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
	player->update(dt);
}

void Engine::render()
{
	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
	SDL_RenderClear(m_Renderer);

	player->draw();

	SDL_RenderPresent(m_Renderer);
}

void Engine::event()
{
	Input::GetInstance()->listen();
}



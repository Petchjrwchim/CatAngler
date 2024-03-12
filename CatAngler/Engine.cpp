#include <iostream>

#include "Engine.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "TextManager.h"
#include "SaveManager.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"
#include "Cat.h"
#include "Camera.h"
#include "Tile.h"
#include "Shop.h"
#include "Menu.h"
#include "Play.h"

Engine* Engine::s_Instance = nullptr;
Menu* menu;
Play play;

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

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
	if (m_Renderer == nullptr) {
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
		return false;
	}

	SoundManager::GetInstance()->loadMusic("bgmusic", "assets/sound/bg_sound.mp3");

	TextureManager::GetInstance()->parseTexture("assets/images/textures.txt");
	
	menu = new Menu();
	menu->init();

	SoundManager::GetInstance()->playMusic("bgmusic");

	return m_IsRunning = true;
}

bool Engine::clean()
{	
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
	

	if (m_GameState == "menu") {
		menu->update();
	}

	if (m_GameState == "prepare") {
		play = Play();
		play.init();
		m_GameState = "play";
	}



	if (m_GameState == "play") play.update();
	
	Input::GetInstance()->handleButtonEvents();
}

void Engine::render()
{
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 10);
	SDL_RenderClear(m_Renderer);

	if (m_GameState == "menu") menu->render();

	if (m_GameState == "play") play.render();
 
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



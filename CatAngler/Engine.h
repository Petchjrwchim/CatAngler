#pragma once
#ifndef ENGINE_H
#define ENGINE_H


#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Engine {

	public:
		static Engine* GetInstance() {
			return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
		}

		bool init();
		bool clean();
		void quit();

		void update();
		void render();
		void event();

		void changeGameState(std::string state) { m_GameState = state; }
		void setPlayerSlot(std::string state) { saveSlot = state; }

		std::string getGameState() { return m_GameState; }
		std::string getPlayerSlot() { return saveSlot; }

		inline bool IsRunning() { return m_IsRunning; }
		inline SDL_Renderer* GetRenderer() { return m_Renderer; }

private:

    Engine() {}
	std::string saveSlot;
	std::string m_GameState = "menu";
    bool m_IsRunning;
    bool m_IsFullscreen = false; 

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    static Engine* s_Instance;

    void toggleFullscreen(); 

};


#endif // !ENGINE_H

#pragma once
#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

class Input
{

	public:
		static Input* GetInstance() {
			return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input;
		}

		void listen();
		bool getKeyDownOnetime(SDL_Scancode key);
		bool getKeyUpOnetime(SDL_Scancode key);
		bool getKeyDown(SDL_Scancode key);
		bool getKeyUp(SDL_Scancode key);

		~Input();

	private:
		Input();
		void keyUp();
		void keyDown();

		Uint8* m_PrevKeyState; 
		const Uint8* m_KeyState;
		static Input* s_Instance;
};

#endif

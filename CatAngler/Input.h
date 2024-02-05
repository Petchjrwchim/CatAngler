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
		bool getKeyDown(SDL_Scancode key);
		bool getKeyUp(SDL_Scancode key);

	private:
		Input();
		void keyUp();
		void keyDown();

		const Uint8* m_KeyState;
		static Input* s_Instance;
};

#endif

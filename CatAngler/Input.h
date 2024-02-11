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

		bool getMouseButtonDownOnetime(int button);
		bool getMouseButtonUpOnetime(int button);
		bool getMouseButtonDown(int button);
		bool getMouseButtonUp(int button);
		bool getMouseButton(int button);
		void getMousePosition(int& x, int& y);

		~Input();

	private:
		Input();
		void keyUp();
		void keyDown();

		int m_MouseState;
		int m_PrevMouseState;
		int m_MouseX, m_MouseY;

		Uint8* m_PrevKeyState; 
		const Uint8* m_KeyState;
		static Input* s_Instance;
};

#endif

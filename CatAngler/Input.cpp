#include "Input.h"
#include "Engine.h"

Input* Input::s_Instance = nullptr;

Input::Input() {
	m_KeyState = SDL_GetKeyboardState(nullptr);
}

void Input::listen()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: Engine::GetInstance()->quit(); break;
		case SDL_KEYDOWN: keyDown(); break;
		case SDL_KEYUP: keyUp(); break;
		}
	}
}

bool Input::getKeyDown(SDL_Scancode key)
{
	if (m_KeyState[key] == 1) 
		return true;
	return false;
}

bool Input::getKeyUp(SDL_Scancode key)
{
	if (m_KeyState[key] != 1)
		return true;
	return false;
}


void Input::keyUp(){
	m_KeyState = SDL_GetKeyboardState(nullptr);
}

void Input::keyDown()
{
	m_KeyState = SDL_GetKeyboardState(nullptr);
}

#include "Input.h"
#include "Engine.h"
#include <map>

Input* Input::s_Instance = nullptr;

Input::Input() {
    m_KeyState = SDL_GetKeyboardState(nullptr);
    m_PrevKeyState = new Uint8[SDL_NUM_SCANCODES];
    memcpy(m_PrevKeyState, m_KeyState, SDL_NUM_SCANCODES);
}

Input::~Input() {
    delete[] m_PrevKeyState;
}

void Input::listen()
{
    memcpy(m_PrevKeyState, m_KeyState, SDL_NUM_SCANCODES);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            Engine::GetInstance()->quit();
            break;
        case SDL_KEYDOWN:
            keyDown();
            break;
        case SDL_KEYUP:
            keyUp();
            break;
        }
    }
}

bool Input::getKeyDownOnetime(SDL_Scancode key)
{
    return m_KeyState[key] == 1 && m_PrevKeyState[key] == 0;
}

bool Input::getKeyUpOnetime(SDL_Scancode key)
{
    return m_KeyState[key] == 0 && m_PrevKeyState[key] == 1;
}

bool Input::getKeyDown(SDL_Scancode key)
{
    return m_KeyState[key] == 1;
}

bool Input::getKeyUp(SDL_Scancode key)
{
    return m_KeyState[key] != 1;
}

void Input::keyUp() {
    m_KeyState = SDL_GetKeyboardState(nullptr);
}

void Input::keyDown()
{
    m_KeyState = SDL_GetKeyboardState(nullptr);
}

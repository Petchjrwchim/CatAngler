#include "Input.h"
#include "Engine.h"
#include <cstring>
#include <iostream>
#include <map>

Input* Input::s_Instance = nullptr;

Input::Input() {
    m_KeyState = SDL_GetKeyboardState(nullptr);
    m_PrevKeyState = new Uint8[SDL_NUM_SCANCODES];

    m_MouseState = 0;
    m_PrevMouseState = 0;
    m_MouseX = m_MouseY = 0;

    memcpy(m_PrevKeyState, m_KeyState, SDL_NUM_SCANCODES);
}

Input::~Input() {
    delete[] m_PrevKeyState;
}

void Input::listen()
{
    m_MouseMoved = false; // Reset the flag at the start of each frame
    memcpy(m_PrevKeyState, m_KeyState, SDL_NUM_SCANCODES);
    m_PrevMouseState = m_MouseState;
    m_MouseState = SDL_GetMouseState(&m_MouseX, &m_MouseY);

    //std::cout << m_MouseX << m_MouseY << std::endl;

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
        case SDL_MOUSEMOTION:
            m_MouseMoved = true; // Set the flag if mouse motion is detected
            break;
        }
        handleSliderEvents(event);
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

bool Input::getMouseMoved() {
    return m_MouseMoved;
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

bool Input::getMouseButtonDownOnetime(int button)
{
    return (m_MouseState & SDL_BUTTON(button)) == 1 && (m_PrevMouseState & SDL_BUTTON(button)) == 0;
}

bool Input::getMouseButtonUpOnetime(int button)
{
    return false;
}

bool Input::getMouseButtonDown(int button) {
    return (m_MouseState & SDL_BUTTON(button)) == 1;
}

bool Input::getMouseButtonUp(int button) {
    return (m_MouseState & SDL_BUTTON(button)) == 0;
}

bool Input::getMouseButton(int button) {
    return (m_MouseState & SDL_BUTTON(button)) != 0;
}

void Input::getMousePosition(int& x, int& y) {
    x = m_MouseX;
    y = m_MouseY;
}

void Input::addButton(int x, int y, int w, int h, std::string p, std::function<void()> onClick, std::function<void()> onHover) {
    bool offset = true;
    for (Button i : m_Buttons) {
        if (i.rect.x == x && i.rect.y == y && i.rect.w == w && i.rect.h == h && i.page == p) {
            offset = false;
        }
    }
    if (offset) m_Buttons.emplace_back(x, y, w, h, p, onClick, onHover);
}

void Input::deleteButton(int n)
{
    if (m_Buttons.size() > n) m_Buttons.erase(m_Buttons.begin() + n, m_Buttons.end());
}

void Input::handleButtonEvents() {
    int x, y;
    SDL_GetMouseState(&x, &y);

    //std::cout << m_Buttons.size() << std::endl;

    for (auto& button : m_Buttons) {
        bool isInside = (x >= button.rect.x) && (x <= (button.rect.x + button.rect.w)) &&
            (y >= button.rect.y) && (y <= (button.rect.y + button.rect.h));

        if (isInside && !getMouseButtonDownOnetime(SDL_BUTTON_LEFT) && currentWindow == button.page) {
            button.onHover();
        }

        if (isInside && getMouseButtonDownOnetime(SDL_BUTTON_LEFT) && currentWindow == button.page) {
            button.onClick();
        }
    }
}

void Input::renderButtons(SDL_Renderer* renderer) {
    for (const auto& button : m_Buttons) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 10);
        if (currentWindow == button.page) {
            SDL_RenderFillRect(renderer, &button.rect);
        }
    }
}

void Input::addSlider(int x, int y, SDL_Renderer* renderer) {
    m_Sliders.emplace_back(x, y, renderer);
}

void Input::renderSliders() {
    for (auto& slider : m_Sliders) {
        slider.draw();
    }
}

void Input::handleSliderEvents(const SDL_Event& e) {
    for (auto& slider : m_Sliders) {
        slider.handleEvent(e);
    }
}
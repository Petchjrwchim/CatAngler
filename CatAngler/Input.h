#pragma once
#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"
#include <functional>
#include <vector>

class Input {
public:
    struct Button {
        SDL_Rect rect; // Position and size of the button
        std::function<void()> onClick; // Callback function for click event
        bool isHovered = false;
        bool isClicked = false;

        Button(int x, int y, int w, int h, std::function<void()> onClickFunc)
            : rect{ x, y, w, h }, onClick(onClickFunc) {}
    };

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

    void addButton(int x, int y, int w, int h, std::function<void()> onClick);
    void handleButtonEvents();
    void renderButtons(SDL_Renderer* renderer);

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

    std::vector<Button> m_Buttons; // List of buttons
};

#endif

#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

const int SLIDER_WIDTH = 300;
const int SLIDER_HEIGHT = 20;

class Slider {
public:
    Slider(int x, int y, SDL_Renderer* renderer);
    void draw() const;
    void handleEvent(const SDL_Event& e);
    bool isMouseInside(int mouseX, int mouseY) const;
    void updateValue(int mouseX);
    int getValue() { return m_value; }

private:

    int m_MaxValue;
    int m_x;
    int m_y;
    int m_value;
    SDL_Renderer* m_renderer;
    bool m_isDragging;

};

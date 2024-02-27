#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <functional>

class Button {
public:
    Button(int x, int y, int width, int height, std::function<void()> onClick);

    void handleEvent(SDL_Event* e);
    void render(SDL_Renderer* renderer);

private:
    SDL_Rect mRect; // The dimensions of the button
    std::function<void()> mOnClick; // The callback function for when the button is clicked
    bool mIsHovered; // Flag to check if the mouse is currently hovering over the button
};

#endif // BUTTON_H


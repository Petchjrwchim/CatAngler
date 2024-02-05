#include "FishingRod.h"
#include "Input.h"
#include "Engine.h"
#include <iostream>

FishingRod* FishingRod::s_Instance = nullptr;

void drawCurve(SDL_Renderer* renderer, int startX, int startY, int length, float* controlX, float* controlY) {
    if (length <= 0) return;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    const int endX = startX + length;
    const int endY = startY + 20;


    *controlX = startX + length / 2;
    *controlY = startY - length / 4;

    for (float t = 0.0; t <= 1.0; t += 0.01) {
        float x = (1 - t) * (1 - t) * startX + 2 * (1 - t) * t * (*controlX) + t * t * endX;
        float y = (1 - t) * (1 - t) * startY + 2 * (1 - t) * t * (*controlY) + t * t * endY;
        SDL_RenderDrawPoint(renderer, (int)x, (int)y);
    }

    int radius = 5; 
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; 
            int dy = radius - h; 
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, endX + dx, endY + dy);
            }
        }
    }
}

void drawMovingCircle(SDL_Renderer* renderer, int startX, int startY, int length, float animationProgress, float controlX, float controlY) {
    if (length <= 0 || animationProgress < 0.0f || animationProgress > 1.0f) return;

    const int endX = startX + length;
    const int endY = startY + 20;

    float x = (1 - animationProgress) * (1 - animationProgress) * startX + 2 * (1 - animationProgress) * animationProgress * controlX + animationProgress * animationProgress * endX;
    float y = (1 - animationProgress) * (1 - animationProgress) * startY + 2 * (1 - animationProgress) * animationProgress * controlY + animationProgress * animationProgress * endY;

    controlX = startX + length / 2;
    controlY = startY - length / 4;

    //for (float t = 0.0; t <= 1.0; t += 0.01) {
    //    float x = (1 - t) * (1 - t) * startX + 2 * (1 - t) * t * (controlX) + t * t * endX;
    //    float y = (1 - t) * (1 - t) * startY + 2 * (1 - t) * t * (controlY) + t * t * endY;
    //    SDL_RenderDrawPoint(renderer, (int)x, (int)y);
    //}

    int radius = 5; 
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int w = -radius; w <= radius; w++) {
        for (int h = -radius; h <= radius; h++) {
            if (w * w + h * h <= radius * radius) {
                SDL_RenderDrawPoint(renderer, (int)x + w, (int)y + h);
            }
        }
    }

    SDL_RenderDrawLine(renderer, startX, startY, (int)x, (int)y);
}


void FishingRod::cast(int x, int y)
{

    if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_H) && !isFKeyPressed) {
        isFKeyPressed = true;
        fKeyPressStartTime = SDL_GetTicks();
        animate = false;
        animationProgress = 0.0f;
    }
    if (Input::GetInstance()->getKeyUp(SDL_SCANCODE_H)) {
        isFKeyPressed = false;
        animate = true;
    }


    if (isFKeyPressed) {
        std::cout << SDL_GetTicks << ", " << fKeyPressStartTime << ", " << ropeLength << std::endl;
        ropeLength = (SDL_GetTicks() - fKeyPressStartTime) / 10;
    }

    if (isFKeyPressed && ropeLength > 0) {
        drawCurve(Engine::GetInstance()->GetRenderer(), x, y, ropeLength, & controlX, & controlY);
    }


    if (animate && ropeLength > 1) {
        animationProgress += 0.02f;
        if (animationProgress > 1.0f) {
            animationProgress = 0.0f;
            animate = false;
            ropeLength = 0;
        }

        drawMovingCircle(Engine::GetInstance()->GetRenderer(), x, y, ropeLength, animationProgress, controlX, controlY);
    }

}
#include <iostream>
#include "SDL.h"
#include "Engine.h"
#include "Timer.h"

using namespace std;

int main(int argc, char* args[]) {

	Engine::GetInstance()->init();

	while (Engine::GetInstance()->IsRunning()) {
		Engine::GetInstance()->event();
		Engine::GetInstance()->update();
		Engine::GetInstance()->render();
		Timer::GetInstance()->Tick();

	}

	Engine::GetInstance()->clean();
	return 0;
}

//#include <SDL.h>
//#include <stdbool.h>
//#include <stdio.h>
//#include <math.h>
//
//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 600;
//
//void drawCurve(SDL_Renderer* renderer, int startX, int startY, int length, float* controlX, float* controlY) {
//    if (length <= 0) return;
//
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//
//    const int endX = startX + length;
//    const int endY = startY + 20;
//
//
//    *controlX = startX + length / 2;
//    *controlY = startY - length / 4;
//
//    for (float t = 0.0; t <= 1.0; t += 0.01) {
//        float x = (1 - t) * (1 - t) * startX + 2 * (1 - t) * t * (*controlX) + t * t * endX;
//        float y = (1 - t) * (1 - t) * startY + 2 * (1 - t) * t * (*controlY) + t * t * endY;
//        SDL_RenderDrawPoint(renderer, (int)x, (int)y);
//    }
//
//    int radius = 5; 
//    for (int w = 0; w < radius * 2; w++) {
//        for (int h = 0; h < radius * 2; h++) {
//            int dx = radius - w; 
//            int dy = radius - h; 
//            if ((dx * dx + dy * dy) <= (radius * radius)) {
//                SDL_RenderDrawPoint(renderer, endX + dx, endY + dy);
//            }
//        }
//    }
//}
//
//void drawMovingCircle(SDL_Renderer* renderer, int startX, int startY, int length, float animationProgress, float controlX, float controlY) {
//    if (length <= 0 || animationProgress < 0.0f || animationProgress > 1.0f) return;
//
//    const int endX = startX + length;
//    const int endY = startY + 20;
//
//    float x = (1 - animationProgress) * (1 - animationProgress) * startX + 2 * (1 - animationProgress) * animationProgress * controlX + animationProgress * animationProgress * endX;
//    float y = (1 - animationProgress) * (1 - animationProgress) * startY + 2 * (1 - animationProgress) * animationProgress * controlY + animationProgress * animationProgress * endY;
//
//    controlX = startX + length / 2;
//    controlY = startY - length / 4;
//
//    for (float t = 0.0; t <= 1.0; t += 0.01) {
//        float x = (1 - t) * (1 - t) * startX + 2 * (1 - t) * t * (controlX) + t * t * endX;
//        float y = (1 - t) * (1 - t) * startY + 2 * (1 - t) * t * (controlY) + t * t * endY;
//        SDL_RenderDrawPoint(renderer, (int)x, (int)y);
//    }
//
//    int radius = 5; 
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//    for (int w = -radius; w <= radius; w++) {
//        for (int h = -radius; h <= radius; h++) {
//            if (w * w + h * h <= radius * radius) {
//                SDL_RenderDrawPoint(renderer, (int)x + w, (int)y + h);
//            }
//        }
//    }
//}
//
//int main(int argc, char* argv[]) {
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//        return -1;
//    }
//
//    SDL_Window* window = SDL_CreateWindow("Fishing Game Prototype - Real-time and Animation",
//        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
//    if (!window) {
//        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
//        SDL_Quit();
//        return -1;
//    }
//
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (!renderer) {
//        SDL_DestroyWindow(window);
//        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
//        SDL_Quit();
//        return -1;
//    }
//
//    bool running = true;
//    SDL_Event event;
//
//    bool isFKeyPressed = false;
//    Uint32 fKeyPressStartTime = 0;
//    float animationProgress = 0.0f; 
//    bool animate = false; 
//    int ropeLength = 0;
//    float controlX = 0, controlY = 0;
//
//    while (running) {
//
//        while (SDL_PollEvent(&event) != 0) {
//            if (event.type == SDL_QUIT) {
//                running = false;
//            }
//            else if (event.type == SDL_KEYDOWN) {
//                if (!isFKeyPressed && event.key.keysym.sym == SDLK_f) {
//                    isFKeyPressed = true;
//                    fKeyPressStartTime = SDL_GetTicks();
//                    animate = false; 
//                    animationProgress = 0.0f;
//                }
//            }
//            else if (event.type == SDL_KEYUP) {
//                if (isFKeyPressed && event.key.keysym.sym == SDLK_f) {
//                    isFKeyPressed = false;
//                    animate = true;
//                }
//            }
//        }
//
//        if (isFKeyPressed) {
//            ropeLength = (SDL_GetTicks() - fKeyPressStartTime) / 10;
//        }
//
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//        SDL_RenderClear(renderer);
//
//        if (isFKeyPressed && ropeLength > 0) {
//            drawCurve(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, ropeLength, &controlX, &controlY);
//        }
//
//
//        if (animate) {
//            animationProgress += 0.02f; 
//            if (animationProgress > 1.0f) {
//                animationProgress = 0.0f; 
//                animate = false;
//                ropeLength = 0;
//            }
//
//            drawMovingCircle(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, ropeLength, animationProgress, controlX, controlY);
//        }
//
//        SDL_RenderPresent(renderer);
//        SDL_Delay(16);
//    }
//
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}

#include "FishingRod.h"
#include "Input.h"
#include "Engine.h"
#include "FishingManager.h"
#include "TextureManager.h"
#include "Cat.h"
#include <iostream>



FishingRod::FishingRod(int id, const std::string& name, const std::string& type, const std::string& texture)
    : Item(id, name, type, texture), isFKeyPressed(false), fKeyPressStartTime(0), animationProgress(0.0f), animate(false), ropeLength(1), controlX(0), controlY(0) {
   
}


void drawCurve(SDL_Renderer* renderer, int startX, int startY, int length, float* controlX, float* controlY, char direction) {
    if (length < 0) return;

    if (direction == 'A') length *= -1;

    const int endX = startX + length;
    const int endY = startY + 20;

    *controlX = startX + length / 2;
    *controlY = startY - abs(length) / 4;

    for (float t = 0.0; t <= 1.0; t += 0.01) {
        float x = (1 - t) * (1 - t) * startX + 2 * (1 - t) * t * (*controlX) + t * t * endX;
        float y = (1 - t) * (1 - t) * startY + 2 * (1 - t) * t * (*controlY) + t * t * endY;
        TextureManager::GetInstance()->draw("point", x, y, 1, 1);
    }

    TextureManager::GetInstance()->draw("aim_point", endX - 15, endY - 15, 32, 32);

}

void drawLine(SDL_Renderer* renderer, int startX, int startY, int length, float* controlX, float* controlY, char direction) {
    if (length < 0) return;

    if (direction == 'W') length *= -1;

    const int endX = startX;
    const int endY = startY + length;
    
    if (direction == 'W') {
        for (int i(0); i >= length; i--) {
            TextureManager::GetInstance()->draw("point", startX, startY + i, 1, 1);
        }
    }
    else {
        for (int i(0); i <= length; i++) {
            TextureManager::GetInstance()->draw("point", startX, startY + i, 1, 1);
        }
    }


    TextureManager::GetInstance()->draw("aim_point", endX - 15, endY - 15, 32, 32);
}

void drawMovingCircle(SDL_Renderer* renderer, int startX, int startY, int length, float animationProgress, float controlX, float controlY, char direction) {
    if (length < 0 || animationProgress < 0.0f || animationProgress > 1.0f) return;

    if (direction == 'A') length *= -1;

    const int endX = startX + length;
    const int endY = startY + 20;

    float x = (1 - animationProgress) * (1 - animationProgress) * startX + 2 * (1 - animationProgress) * animationProgress * controlX + animationProgress * animationProgress * endX;
    float y = (1 - animationProgress) * (1 - animationProgress) * startY + 2 * (1 - animationProgress) * animationProgress * controlY + animationProgress * animationProgress * endY;

    controlX = startX + length / 2;
    controlY = startY - abs(length) / 4;

    const int segmentSize = 1; 
    const float lineLength = sqrt(pow((float)endX - startX, 2) + pow((float)endY - startY, 2));
    const int numSegments = (int)(lineLength / segmentSize);
    float segmentX{};
    float segmentY{};
    for (int i = 0; i <= numSegments; i++) {
        float segmentProgress = (float)i / numSegments;
        segmentX = startX + segmentProgress * (x - startX);
        segmentY = startY + segmentProgress * (y - startY);
        TextureManager::GetInstance()->draw("point", segmentX, segmentY, segmentSize, segmentSize);
    }

    TextureManager::GetInstance()->draw("aim_point", segmentX - 15, segmentY - 15, 32, 32);
    
}


void drawMovingLine(SDL_Renderer* renderer, int startX, int startY, int length, float animationProgress, float controlX, float controlY, char direction) {
    if (length < 0 || animationProgress < 0.0f || animationProgress > 1.0f) return;

    if (direction == 'W') length *= -1;

    const int endX = startX;
    const int endY = startY + length;

    float x = startX; 
    float y = startY + length * animationProgress;

    const int segmentSize = 1;
    const float lineLength = sqrt(pow((float)endX - startX, 2) + pow((float)endY - startY, 2));
    const int numSegments = (int)(lineLength / segmentSize);
    float segmentX{};
    float segmentY{};
    for (int i = 0; i <= numSegments; i++) {
        float segmentProgress = (float)i / numSegments;
        segmentX = startX + segmentProgress * (x - startX);
        segmentY = startY + segmentProgress * (y - startY);
        TextureManager::GetInstance()->draw("point", segmentX, segmentY, segmentSize, segmentSize);
    }
    TextureManager::GetInstance()->draw("aim_point", segmentX - 15, segmentY - 15, 32, 32);
}


void FishingRod::use(char direction, int x, int y)
{
    
    if (Input::GetInstance()->getMouseButtonDown(1) && !isFKeyPressed) {
        isFKeyPressed = true;
        fKeyPressStartTime = SDL_GetTicks();
        animate = false;
        animationProgress = 0.0f;
    }
    if (Input::GetInstance()->getMouseButtonUp(1)) {
        isFKeyPressed = false;
        animate = true;
    }


    if (isFKeyPressed) {
        //std::cout << SDL_GetTicks << ", " << fKeyPressStartTime << ", " << ropeLength << std::endl;
        ropeLength = (SDL_GetTicks() - fKeyPressStartTime) / 10;
    }

    if (isFKeyPressed && ropeLength > 0) {
        if (direction == 'S' || direction == 'W') {
            drawLine(Engine::GetInstance()->GetRenderer(), x, y, ropeLength, &controlX, &controlY, direction);
        }
        else {
            drawCurve(Engine::GetInstance()->GetRenderer(), x, y, ropeLength, &controlX, &controlY, direction);
        }
   
    }

    if (animate && ropeLength > 1) {
        animationProgress += 0.01f;
        if (animationProgress > 1.0f) {
            animationProgress = 0.0f;
            animate = false;
            ropeLength = 0;
        }
        if (direction == 'S' || direction == 'W') {
            drawMovingLine(Engine::GetInstance()->GetRenderer(), x, y, ropeLength, animationProgress, controlX, controlY, direction);
        }
        else {
            drawMovingCircle(Engine::GetInstance()->GetRenderer(), x, y, ropeLength, animationProgress, controlX, controlY, direction);
        }
        
    }

    
}


std::string FishingRod::getDescription() const
{
    return std::string();
}

void FishingRod::draw(char direction, int x, int y)
{
    TextureManager::GetInstance()->draw("fishingrod", x, y, 64, 64);
    if (animationProgress > 0.99f) {
        int fishCheckX = x, fishCheckY = y;
        switch (direction) {
        case 'W': fishCheckY -= ropeLength; break;
        case 'A': fishCheckX -= ropeLength; break;
        case 'S': fishCheckY += ropeLength; break;
        case 'D': fishCheckX += ropeLength; break;
        }

        FishingManager::GetInstance()->checkFishingPosition(fishCheckX, fishCheckY, "Water");
    }
}

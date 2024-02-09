#include "FishingRod.h"
#include "Input.h"
#include "Engine.h"
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


void FishingRod::use()
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
        if (m_Direction == 'S' || m_Direction == 'W') {
            drawLine(Engine::GetInstance()->GetRenderer(), m_X, m_Y, ropeLength, &controlX, &controlY, m_Direction);
        }
        else {
            drawCurve(Engine::GetInstance()->GetRenderer(), m_X, m_Y, ropeLength, &controlX, &controlY, m_Direction);
        }
   
    }

    if (animate && ropeLength > 1) {
        animationProgress += 0.01f;
        if (animationProgress > 1.0f) {
            animationProgress = 0.0f;
            animate = false;
            ropeLength = 0;
        }
        if (m_Direction == 'S' || m_Direction == 'W') {
            drawMovingLine(Engine::GetInstance()->GetRenderer(), m_X, m_Y, ropeLength, animationProgress, controlX, controlY, m_Direction);
        }
        else {
            drawMovingCircle(Engine::GetInstance()->GetRenderer(), m_X, m_Y, ropeLength, animationProgress, controlX, controlY, m_Direction);
        }
        
    }

    
}

std::string FishingRod::getDescription()
{
    return std::string();
}

void FishingRod::draw()
{
    TextureManager::GetInstance()->draw("fishingrod", m_X, m_Y, 64, 64);

}

int FishingRod::getX()
{
    if (animationProgress > 0.99f) {
        int fishCheckX = m_X, fishCheckY = m_Y;
        switch (m_Direction) {
        case 'A': return fishCheckX -= ropeLength; break;
        case 'D': return fishCheckX += ropeLength; break;
        default :  return fishCheckX;
        }

    }
}

int FishingRod::getY()
{
    if (animationProgress > 0.99f) {
        int fishCheckX = m_X, fishCheckY = m_Y;
        switch (m_Direction) {
        case 'W': return fishCheckY -= ropeLength; break;
        case 'S': return fishCheckY += ropeLength; break;
        default : return fishCheckY;
        }

    }
}

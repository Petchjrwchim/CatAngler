#include "FishingRod.h"
#include "Engine.h"
#include "TextureManager.h"
#include "Cat.h"
#include <iostream>



FishingRod::FishingRod(int quantity, const std::string& name, const std::string& type, const std::string& texture, int price)
    : Item(quantity, name, type, texture, price), isMousePressed(false), fKeyPressStartTime(0), animationProgress(0.0f), animate(false), ropeLength(1), controlX(0), controlY(0) {

    m_Aimation = new Animation();
    m_Aimation->setProps("bait", 1, 1, 100);

}


void drawCurve(SDL_Renderer* renderer, int startX, int startY, int length, float* controlX, float* controlY, char direction) {
    if (length < 0) return;

    startY += 3;

    if (direction == 'A') {
        length *= -1;
        startX -= 23;
    }
    else {
        startX += 23;
    }
        

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

void FishingRod::drawMovingCircle(SDL_Renderer* renderer, int startX, int startY, int length, float animationProgress, float controlX, float controlY, char direction) {
    if (length < 0 || animationProgress < 0.0f) return;

    startY += 3;

    if (direction == 'A') {
        length *= -1;
        startX -= 23;
    }
    else {
        startX += 23;
    }

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

    m_Aimation->draw(segmentX - 15, segmentY - 15, 32, 32);
    //TextureManager::GetInstance()->draw("bait", segmentX - 15, segmentY - 15, 32, 32);
    
}


void FishingRod::drawMovingLine(SDL_Renderer* renderer, int startX, int startY, int length, float animationProgress, float controlX, float controlY, char direction) {
    if (length < 0 || animationProgress < 0.0f) return;

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

    m_Aimation->draw(segmentX - 15, segmentY - 15, 32, 32);
    //TextureManager::GetInstance()->draw("aim_point", segmentX - 15, segmentY - 15, 32, 32);
}


void FishingRod::use()
{
    srand(time(NULL));
    
    if (Input::GetInstance()->getMouseButtonDown(1) && !isMousePressed && QTEstate == 0 ) {
        m_Aimation->setProps("bait", 1, 1, 100);
        isMousePressed = true;
        fKeyPressStartTime = SDL_GetTicks();
        oldPressStartTime = fKeyPressStartTime;
        waitTime = 5;
        animate = false;
        animationProgress = 0.0f;
    }
    if (Input::GetInstance()->getMouseButtonUp(1) && QTEstate == 0) {
        isMousePressed = false;
        animate = true;
    }

    if (isMousePressed && QTEstate == 0) {
        //std::cout << SDL_GetTicks << ", " << fKeyPressStartTime << ", " << ropeLength << std::endl;as
        ropeLength = (SDL_GetTicks() - fKeyPressStartTime) / 10;
    }

    if (isMousePressed && ropeLength > 10 && QTEstate == 0) {
        if (m_Direction == 'S' || m_Direction == 'W') {
            drawLine(Engine::GetInstance()->GetRenderer(), m_X, m_Y, ropeLength, &controlX, &controlY, m_Direction);
        }
        else {
            drawCurve(Engine::GetInstance()->GetRenderer(), m_X, m_Y, ropeLength, &controlX, &controlY, m_Direction);
        }
   
    }

    if (animate && ropeLength > 10) {
 
        if (animationProgress > 1.0f) {
            qteEvent();
        }
        else {
            animationProgress += 0.01f;
        }

        if (animationProgress == 0.99f) {
            QTEstate += 1;
        }
        
        if (m_Direction == 'S' || m_Direction == 'W') {
            drawMovingLine(Engine::GetInstance()->GetRenderer(), m_X, m_Y, ropeLength, animationProgress, controlX, controlY, m_Direction);
        }
        else {
            drawMovingCircle(Engine::GetInstance()->GetRenderer(), m_X, m_Y, ropeLength, animationProgress, controlX, controlY, m_Direction);
        }
        
    }

    m_Aimation->update();
}

std::string FishingRod::getDescription()
{
    return "Use for fishing";
}

void FishingRod::draw()
{
    if (m_Direction == 'W') {
        TextureManager::GetInstance()->draw("fishingrod_front", m_X - 15, m_Y - 3, 32, 10);
    }
    if (m_Direction == 'A') {
        TextureManager::GetInstance()->draw("fishingrod", m_X - 27, m_Y, 32, 32, SDL_FLIP_HORIZONTAL);
    }
    if (m_Direction == 'S') {
        TextureManager::GetInstance()->draw("fishingrod_front", m_X - 15, m_Y, 32, 32);
    }
    if (m_Direction == 'D') {
        TextureManager::GetInstance()->draw("fishingrod", m_X - 5, m_Y, 32, 32);
        
    }

}

int FishingRod::getX()
{

    if (animationProgress > 0.99f && isSuccess) {
        int fishCheckX = m_X;
        switch (m_Direction) {
        case 'A': fishCheckX -= ropeLength; break;
        case 'D': fishCheckX += ropeLength; break;
        default : fishCheckX;
        }
        return fishCheckX;
    }
    else if (ropeLength > 10) {
        return m_X;
    }
    else {
        return 0;;
    }
}

int FishingRod::getY()
{
    if (animationProgress > 0.99f && isSuccess) {
        int fishCheckY = m_Y;
        animationProgress = 0.0f;
        isSuccess = false;
        switch (m_Direction) {
        case 'W': fishCheckY -= ropeLength; break;
        case 'S': fishCheckY += ropeLength; break;
        default : fishCheckY;
        }
        ropeLength = 0;
        return fishCheckY;
    }
    else if (ropeLength > 10) {
        return  m_Y;
    }
    else {
        return 0;
    }
}

void FishingRod::qteEvent(int x, int y) {

    

    if (QTEstate <= 3 && (SDL_GetTicks() - oldPressStartTime) / 1000 > ropeLength/100 + waitTime) {

        
        if (Input::GetInstance()->getMouseButtonDown(1)) {
            m_Aimation->setProps("bait", 1, 1, 100);
            if (QTEstate <= 2) {
                int hookTime = rand() % 3 + 1;
                waitTime += hookTime;
            }
            isMousePressed = false;
        }

        if (Input::GetInstance()->getMouseButtonUp(1) && !isMousePressed) {
            m_Aimation->setProps("bait", 1, 4, 100);
            isMousePressed = true;
            QTEstate += 1;
            fKeyPressStartTime = SDL_GetTicks();
        }

        if (isMousePressed) {
            shakeTime = (SDL_GetTicks() - fKeyPressStartTime) / 1000;
        }


        if (shakeTime > 2) {
            //std::cout << "unsuccess hook" << std::endl;
            isMousePressed = true;
            isSuccess = false;
            animate = false;
            animationProgress = 0.0f;
            ropeLength = 0;
            QTEstate = 0;
        }

        //std::cout << "hook, " << QTEstate <<", "<< shakeTime << ", " << waitTime << std::endl;

    }
    if (QTEstate > 3) {
        //std::cout << "qte > 3" << animationProgress << std::endl;
        isSuccess = true;
        animate = false;
        QTEstate = 0;
    }
}
#pragma once
#include "Item.h"
#include "Animation.h"
#include <string>


struct SDL_Renderer;
struct SDL_Texture;

class FishingRod : public Item {

private:

    Animation* m_Aimation;

    int QTEstate = 0;
    int waitTime;
    int shakeTime;

    bool isSuccess = false;
    bool isMousePressed;
    Uint32 fKeyPressStartTime;
    Uint32 oldPressStartTime;
    float animationProgress;
    bool animate;
    int ropeLength;
    float controlX, controlY;

public:
    FishingRod(int quantity, const std::string& name, const std::string& type, const std::string& texture);

    std::string getDescription() override;

    void drawMovingLine(SDL_Renderer* renderer, int startX, int startY, int length, float animationProgress, float controlX, float controlY, char direction);
    void drawMovingCircle(SDL_Renderer* renderer, int startX, int startY, int length, float animationProgress, float controlX, float controlY, char direction);
    void qteEvent(int x = 0, int y = 0);

    void use() override;
    void draw() override;

    int getX() override;
    int getY() override;

};

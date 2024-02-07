#pragma once
#include "Item.h"
#include <string>


struct SDL_Renderer;
struct SDL_Texture;

class FishingRod : public Item {
public:
    FishingRod(int id, const std::string& name, const std::string& type, const std::string& texture);

    void use(char direction, int x, int y) override;
    std::string getDescription() const override;
    void draw(int x, int y) override;

private:
    bool isFKeyPressed;
    Uint32 fKeyPressStartTime;
    float animationProgress;
    bool animate;
    int ropeLength;
    float controlX, controlY;

};

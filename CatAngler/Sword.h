#pragma once
#include "Item.h"

class Sword: public Item
{
private:

public:
    void use() override;
    void draw() override;

    int getX() override;
    int getY() override;
};


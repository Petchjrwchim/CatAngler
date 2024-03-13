#pragma once
#include "Item.h"

class Food  : public Item
{
private:
    int m_Heal;

public:
    Food(int quantity, const std::string& name, const std::string& type, const std::string& texture, int price, int heal = 0);

    std::string getDescription() override;

    void use() override;
    void draw() override;

    Food* clone() const override {
        return new Food(*this);
    }

};


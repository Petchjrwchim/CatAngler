#pragma once
#include "Item.h" 
#include <string>

class Fish : public Item { 
private:
    int size;

public:

    Fish(int quantity, const std::string& name, int size, const std::string& texture, int price, int chance)
        : Item(quantity, name, "Fish", texture, price, chance), size(size) {}


    virtual std::string getDescription() override {
        return "Name: " + Fish::getName() + ", Size: " + std::to_string(size);
    }

    inline int getSize() const { return size; }

    virtual void use() override {
    }

    void draw() override;
};

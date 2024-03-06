#pragma once
#include "Item.h" 
#include <string>

class Fish : public Item { 
private:
    int size;
    std::string rarity;

public:

    Fish(int quantity, const std::string& name, int size, const std::string& rarity, const std::string& texture, int price)
        : Item(quantity, name, "Fish", texture, price), size(size), rarity(rarity) {}


    virtual std::string getDescription() override {
        return "Name: " + Fish::getName() + ", Size: " + std::to_string(size) + ", Rarity: " + rarity;
    }

    inline int getSize() const { return size; }
    inline std::string getRarity() const { return rarity; }

    virtual void use() override {
    }

    void draw() override;
};

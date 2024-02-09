#pragma once
#include "Item.h" 
#include <string>

class Fish : public Item { 
private:
    int size;
    std::string rarity;

public:

    Fish(int id, const std::string& name, int size, const std::string& rarity, const std::string& texture)
        : Item(id, name, "Fish", texture), size(size), rarity(rarity) {}


    virtual std::string getDescription() override {
        return "Name: " + Fish::getName() + ", Size: " + std::to_string(size) + ", Rarity: " + rarity;
    }

    inline int getSize() const { return size; }
    inline std::string getRarity() const { return rarity; }

    virtual void use() override {
    }

    void draw() override {
    }

};

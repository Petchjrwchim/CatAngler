#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "SDL.h"
#include "TextureManager.h"
#include "Collider.h"
#include <string>
#include "Input.h"
#include "Enemy.h"

class Item {
    public:

        int m_X, m_Y;
        char m_Direction;
        std::vector<Enemy*> m_enemies;

        Item(int quantity, const std::string& name, const std::string& type, const std::string& texture, const int price)
            : m_Quantity(quantity), m_Name(name), m_Type(type), m_TextureID(texture), m_Price(price) {}

        virtual void use() = 0;
        virtual std::string getDescription() = 0;
        virtual void draw() = 0;
        virtual int getX() { return m_X; }
        virtual int getY() { return m_Y; }

        void update(char direction, int x = 0, int y = 0, std::vector<Enemy*> enemies = {}) {
            m_Direction = direction;
            m_X = x;
            m_Y = y;
            m_enemies = enemies;
        }

        void additems(int amount) {
            m_Quantity += amount;
        }

        void removeitems(int amount) {
            m_Quantity -= amount;
            if (m_Quantity < 1) m_Quantity = 0; 
        }

        int getQuantity() { return m_Quantity; }
        int getPrice() { return m_Price; }

        std::string getID() { return m_TextureID; }
        std::string getName() { return m_Name; }
        std::string getType() { return m_Type; }

    private:

        int m_Quantity;
        int m_Price;
        std::string m_Type;
        std::string m_Name;
        std::string m_TextureID;
};

#endif // ITEM_H

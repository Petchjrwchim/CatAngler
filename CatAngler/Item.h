#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "SDL.h"
#include "TextureManager.h"
#include <string>

class Item {
    public:

        int m_X, m_Y;
        char m_Direction;

        Item(int quantity, const std::string& name, const std::string& type, const std::string& texture)
            : m_Quantity(quantity), m_Name(name), m_Type(type), m_TextureID(texture) {}

        virtual void use() = 0;
        virtual std::string getDescription() = 0;
        virtual void draw() = 0;
        virtual int getX() { return m_X; }
        virtual int getY() { return m_Y; }
        void update(char direction, int x = 0, int y = 0) {
            m_Direction = direction;
            m_X = x;
            m_Y = y;
        }

        void additems(int amount) {
            m_Quantity += amount;
        }

        std::string getID() { return m_TextureID; }
        int getQuantity() { return m_Quantity; }
        std::string getName() { return m_Name; }
        std::string getType() { return m_Type; }

    private:
        
        int m_Quantity;
        std::string m_Type;
        std::string m_Name;
        std::string m_TextureID;
};

#endif // ITEM_H
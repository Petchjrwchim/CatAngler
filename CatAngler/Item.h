#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "SDL.h"
#include "TextureManager.h"
#include <string>

class Item {
    public:

        std::string m_Name;

        Item(int id, const std::string& name, const std::string& type, const std::string& texture);

        virtual void use(char direction, int x = 0, int y = 0);
        virtual std::string getDescription() const;
        virtual void draw(char direction, int x = 0, int y = 0);
        void update(float dt);
        void clean();

        std::string getID() { return m_TextureID; }
        std::string getName() { return m_Name; }

    private:
        std::string m_TextureID;
};

#endif // ITEM_H

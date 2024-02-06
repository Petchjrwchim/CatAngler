#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "SDL.h"
#include <string>

class Item {
    public:

        Item(int id, const std::string& name, const std::string& type, const std::string& texture);

        virtual void use(int x = 0, int y = 0);
        virtual std::string getDescription() const;
        void draw();
        void update(float dt);
        void clean();

        std::string getID() { return m_TextureID; }
    private:
        std::string m_TextureID;
};

#endif // ITEM_H

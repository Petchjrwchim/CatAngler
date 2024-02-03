#pragma once

#include "SDL.h"
#include "Tile.h"
#include <vector>
#include "Engine.h"
#include "tileson.hpp"

class CollisionHandler
{
public:
    CollisionHandler();
    static CollisionHandler* GetInstance() {
        if (s_Instance == nullptr) {
            s_Instance = new CollisionHandler();
        }
        return s_Instance;
    }

    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
    bool mapCollision(const SDL_Rect& a);

private:
    std::vector<std::vector<uint32_t>> m_CollisionMap;
    static CollisionHandler* s_Instance;
};

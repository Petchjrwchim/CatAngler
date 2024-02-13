#pragma once

#include "SDL.h"
#include "Tile.h"
#include <vector>
#include "Engine.h"
#include "tileson.hpp"
#include "Collider.h"

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
    bool checkCollisionVec(Collider* a, std::vector<Collider*> b);
    bool mapCollision(const SDL_Rect& a, std::string layerName = "Collision");

private:
    std::string layerName;
    std::vector<std::vector<uint32_t>> m_CollisionMap;
    static CollisionHandler* s_Instance;
};

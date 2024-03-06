#pragma once

#include "Inventory.h"
#include "Collider.h"
#include "Fish.h"

class FishingManager {
    private:

        std::vector<Fish*> fishInArea;
        Collider* m_Collider;
        static FishingManager* s_Instance;
        Inventory* playerInventory;

        std::vector<Collider*>* colliderVec;
        std::vector<Enemy*> spawned_enemies;

    public:

        FishingManager(Inventory* player_Inv = nullptr , std::vector<Collider*>* colliderVec = {});

        inline static FishingManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new FishingManager(); }

        std::vector<Enemy*> getEnemies() { return spawned_enemies; }

        void checkFishing(int  x,int y, std::string map);

        void update(float dt, int x, int y, int* health, SDL_Rect target);

        void draw();
};
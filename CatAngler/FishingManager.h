#pragma once

#include "Fish.h"
#include "FishingRod.h"
#include <vector>
#include "SDL.h"


class FishingManager {
    private:
        FishingRod* rod = FishingRod::GetInstance();;
        std::vector<Fish*> fishInArea;
        static FishingManager* s_Instance;

    public:
        FishingManager(){}

        FishingManager(FishingRod* rod, std::vector<Fish*> fishInArea)
            : rod(rod), fishInArea(fishInArea) {}

        inline static FishingManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new FishingManager(); }

        void castRod();

        void update(bool input, int x, int y);
};
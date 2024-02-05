#pragma once
#include "SDL.h"

class FishingRod
{
	public:

        FishingRod(){}

	    bool isFKeyPressed = false;
        Uint32 fKeyPressStartTime = 0;
        float animationProgress = 0.0f; 
        bool animate = false; 
        int ropeLength = 1;
        float controlX = 0, controlY = 0;

	    void cast(int x, int y);
        inline static FishingRod* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new FishingRod(); }

    private:
        static FishingRod* s_Instance;
        
};


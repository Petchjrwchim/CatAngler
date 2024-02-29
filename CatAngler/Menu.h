#pragma once
#include "SDL.h"

class Menu
{
public:
	static Menu* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Menu();
	}

	void render();

private:
	static Menu* s_Instance;
};


#pragma once
#include "SDL.h"
#include "Input.h" 
#include "SDL_Image.h"
#include "GameState.h"

#include <iostream>

class Play : public GameState
{
public:
	Play();
	virtual bool init();
	virtual bool exit();
	virtual void update();
	virtual void render();

private:

	static void openMenu();
	static void pauseGame();

};

#pragma once
#include "SDL.h"
#include "Input.h" 
#include "Animation.h"
#include "SDL_Image.h"
#include "GameState.h"

#include <iostream>

class Menu: public GameState
{
public:
	Menu();
	virtual bool init();
	virtual bool exit();
	virtual void update();
	virtual void render();

private:
	
	Animation* m_Aimation;

	static void startGame();
	static void settings();
	static void quit();

	void initButtons();
	void setCursor(const char* imagePath);

private:

	SDL_Renderer* m_Ctxt;
	SDL_Cursor* cursor;
};


#pragma once
#include "SDL.h"
#include "Input.h" 
#include "Animation.h"
#include "SDL_Image.h"
#include "GameState.h"
#include "Camera.h"
#include <iostream>

class Menu: public GameState
{
public:
	inline static Menu* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Menu(); }
	Menu();
	virtual bool init();
	virtual bool exit();
	virtual void update();
	virtual void render();
	void renderSaveScreen(Vector2D cam);
	void renderSettings(Vector2D cam);
	void renderSelected(Vector2D cam);

	std::string currentTab = "menu";
	std::string IsSelecting;

private:

	static Menu* s_Instance;
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


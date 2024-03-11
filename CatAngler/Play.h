#pragma once
#include "SDL.h"
#include "Input.h" 
#include "SDL_Image.h"
#include "GameState.h"
#include "Item.h"
#include <map>
#include <iostream>

class Play : public GameState
{
public:
	Play(){}

	//inline static Play* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Play(); }
	std::unordered_map<std::string, int> loadedData;
	std::vector<std::pair<int, int>> unlockFish;
	std::unordered_map<std::string, int> gameData;

	Item* fish = NULL;
	bool show = false;
	bool IsPause = false;
	bool IsCollection = false;

	virtual bool init();
	virtual bool exit();
	virtual void update();
	virtual void render();
	void renderCollection();
	void initButton();

private:

	static Play* s_Instance;
	static void openMenu();
	static void pauseGame();

};

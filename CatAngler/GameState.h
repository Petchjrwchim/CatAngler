#pragma once

class GameState
{
public:
	virtual bool init() = 0;
	virtual bool exit() = 0;

	virtual void update() = 0;
	virtual void render() = 0;
};



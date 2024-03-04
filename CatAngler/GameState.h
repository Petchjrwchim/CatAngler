#pragma once

class GameState
{
public:
	virtual bool Init() = 0;
	virtual bool Exit() = 0;

	virtual void update() = 0;
	virtual void render() = 0;
};



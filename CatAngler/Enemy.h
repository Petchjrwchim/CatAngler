#pragma once

#include "Character.h"
#include "Collider.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Vector2D.h"

#define SPEED 0.2f

class Enemy : public Character
{
private:

	int t_X, t_Y;

	char lastDirection = 'S';

	bool m_IsMoving;

	int m_Health;

	SDL_RendererFlip m_Flip;
	SDL_Rect m_Target;

	Collider* m_Collider;
	Animation* m_Aimation;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition;

public:
	Enemy(Properties* props, int health);

	void setTarget(int x, int y, SDL_Rect target);
	int getHealth() { return health; }

	virtual void draw();
	virtual void update(float dt);
	virtual void clean();
};


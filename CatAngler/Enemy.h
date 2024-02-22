#pragma once

#include "Character.h"
#include <vector>
#include "Collider.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Vector2D.h"

#define SPEED 0.5f

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
	Animation* m_AimationE;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition;

	std::vector<Collider*> colliderVec;

public:
	Enemy(Properties* props, int health);

	void setColliderVec(std::vector<Collider*> v) { colliderVec = v; }
	std::vector<Collider*> getColliderVec() { return colliderVec; }

	void setTarget(int x, int y, SDL_Rect target);
	int getHealth() { return health; }

	void reduceHealth(int dmg) { health -= dmg; }

	Collider* getCollider() { return m_Collider; };
	virtual void draw();
	virtual void update(float dt);
	virtual void clean();
};


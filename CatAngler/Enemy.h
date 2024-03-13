#pragma once

#include "Character.h"
#include <vector>
#include "Collider.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Vector2D.h"

#define SPEED_ENEMY 1.0f

class Enemy : public Character
{
private:

	int t_X, t_Y;
	int m_Frame;
	char lastDirection = 'S';

	bool m_IsMoving;

	int attackTime = 0;
	bool firstHit = true;

	SDL_RendererFlip m_Flip;
	SDL_Rect m_Target;

	Collider* m_Collider;
	Animation* m_AimationE;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition;

	int* m_playerHealth;
	int h;

	std::vector<Collider*> colliderVec;

public:
	Enemy(Properties* props, int health, int frame);

	void setColliderVec(std::vector<Collider*> v) { colliderVec = v; }
	std::vector<Collider*> getColliderVec() { return colliderVec; }

	void setTarget(int x, int y, int* health, SDL_Rect target);

	Collider* getCollider() { return m_Collider; };
	virtual void draw();
	virtual void update(float dt);
	virtual void clean();
};


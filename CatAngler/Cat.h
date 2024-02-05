#ifndef CAT.H

#include "Character.h"
#include "Collider.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Vector2D.h"

#define SPEED 20.0f

class Cat : public Character {

private:

	char lastDirection = 'W';
	bool m_IsFishing;
	bool m_IsWalking;
	bool m_IsWalkingForward;
	bool m_IsWalkingBackwward;
	bool m_IsIdle;
	SDL_RendererFlip m_Flip;

	Collider* m_Collider;
	Animation* m_Aimation;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition;

public:

	Cat(Properties* props);
	bool getFishing() { return m_IsFishing; }
	int getX();
	int getY();
	virtual void draw();
	virtual void update(float dt);
	virtual void clean();


};

#endif // !CAT.H

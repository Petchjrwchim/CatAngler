#ifndef CAT.H

#include "Character.h"
#include "Collider.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Inventory.h"
#include "Vector2D.h"

#define SPEED 50.0f

class Cat : public Character {

private:

	char lastDirection = 'S';
	bool m_IsFishing;
	bool m_IsMoving;
	int m_IsUsing = 0;
	int current_Equip = 1;
	SDL_RendererFlip m_Flip;

	Collider* m_Collider;
	Animation* m_Aimation;
	Inventory* m_Inventory;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition;

	std::vector<Collider*> colliderVec;

public:

	Cat(Properties* props);
	Inventory* getInventory() { return m_Inventory; }
	bool getFishing() { return m_IsFishing; }
	char getDirection() { return lastDirection; }
	
	int getX();
	int getY();
	int getTX();
	int getTY();


	void drawInv();
	void equip();

	virtual void draw();
	virtual void update(float dt);
	virtual void clean();


};

#endif // !CAT.H

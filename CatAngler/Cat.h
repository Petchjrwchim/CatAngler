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
	bool m_IsInteract = false;
	bool m_IsShopping = false;
	int m_IsUsing = 0;
	int current_Equip = 1;
	int m_Coin = 10000;
	int* catHealth = NULL;
	SDL_RendererFlip m_Flip;

	Collider* m_Collider;
	Animation* m_Aimation;
	Inventory* m_Inventory;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition;

	std::vector<Collider*> colliderVec;

	int checkX, checkY;

public:
	
	Cat(Properties* props);
	Inventory* getInventory() { return m_Inventory; }
	bool getFishing() const { return m_IsFishing; }
	char getDirection() const { return lastDirection; }
	bool getInteract() const { return m_IsInteract; }
	bool getIs_Shopping() const {return m_IsShopping;}

	int& getCoin() { return m_Coin; }

	void setCoin(int coin) { m_Coin = coin; }
	void setInteract(bool set) { m_IsInteract = set; }

	int getX();
	int getY();
	int getTX();
	int getTY();
	Vector2D getCam();


	void drawInv();
	void equip();

	virtual void draw();
	virtual void update(float dt);
	virtual void clean();


};

#endif // !CAT.H

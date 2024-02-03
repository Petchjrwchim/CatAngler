#ifndef CAT.H

#include "Character.h"
#include "Collider.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Vector2D.h"

class Cat: public Character{
	public:
		Cat(Properties* props);

		virtual void draw();
		virtual void update(float dt);
		virtual void clean();

	private:

		Collider* m_Collider;
		Animation* m_Aimation;
		RigidBody* m_RigidBody;
		Vector2D m_LastSafePosition;
};

#endif // !CAT.H

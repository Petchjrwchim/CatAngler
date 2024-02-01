#ifndef CAT.H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

class Cat: public Character{
	public:
		Cat(Properties* props);

		virtual void draw();
		virtual void update(float dt);
		virtual void clean();

	private:

		Animation* m_Aimation;
		RigidBody* m_RigidBody;
};

#endif // !CAT.H

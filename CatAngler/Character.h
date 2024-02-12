#pragma once
#ifndef CHARACTER.H

#include "GameObject.h"
#include <string>

class Character : public GameObject {

	public:

		Character() {}

		Character(Properties* props): GameObject(props) {}

		virtual void draw() = 0;
		virtual void update(float dt) = 0;
		virtual void clean() = 0;

	protected:
		std::string m_Name;
		int health = 10;
};

#endif // !CHARACTER.H

#pragma once
#ifndef CHARACTER.H

#include "GameObject.h"
#include <string>

class Character : public GameObject {

	public:
		Character() {}

		Character(Properties* props): GameObject(props) {}

		int getHealth() { return m_Health; }
		void reduceHealth(int dmg) { m_Health -= dmg; }

		virtual void draw() = 0;
		virtual void update(float dt) = 0;
		virtual void clean() = 0;

	protected:
		std::string m_Name;
		int m_Health = 10;
};

#endif // !CHARACTER.H

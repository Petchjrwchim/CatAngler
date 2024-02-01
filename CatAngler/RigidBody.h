#pragma once
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "SDL.h"
#include <Vector2D.h>

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

#define FORWARD 1
#define BACKWARD -1

class RigidBody
{
public:
	RigidBody() {
		m_Mass = UNI_MASS;
		m_Gravity = GRAVITY;
	}

	// gravity and mass
	inline void setMass(float mass) { m_Mass = mass; }
	inline void setGravity(float gravity) { m_Gravity = gravity; }

	// force
	inline void applyForce (Vector2D F) { m_Force = F;}
	inline void applyForceX(float Fx) { m_Force.X = Fx; }
	inline void applyForceY(float Fy) { m_Force.Y = Fy; }
	inline void unsetForce() { m_Force = Vector2D(0, 0); }

	// friction
	inline void applyFriction(Vector2D Fr) { m_Friction = Fr; }
	inline void unsetFriction() { m_Friction = Vector2D(0, 0); }

	inline float getMass() { return m_Mass; }
	inline Vector2D position() { return m_Position; }
	inline Vector2D velocity() { return m_Velocity; }
	inline Vector2D acceleration() { return m_Acceleration; }

	void update(float dt) {
		m_Acceleration.X = (m_Force.X + m_Friction.X) / m_Mass;
		m_Acceleration.Y = (m_Force.Y + m_Friction.Y) / m_Mass;
		m_Velocity.X = m_Acceleration.X * dt;
		m_Velocity.Y = m_Acceleration.Y * dt;
		m_Position.X = m_Velocity.X * dt;
		m_Position.Y = m_Velocity.Y * dt;
		//SDL_Log("%f, %f", dt, m_Position.X);
	}

	private:
		float m_Mass; 
		float m_Gravity;

		Vector2D m_Force;
		Vector2D m_Friction;

		Vector2D m_Position;
		Vector2D m_Velocity;
		Vector2D m_Acceleration;
};

#endif
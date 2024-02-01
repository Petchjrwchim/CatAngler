#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"

class Transform
{
	public:
		float X, Y;

		Transform(float x=0, float y=0): X(x), Y(y) {}

		void log(std::string msg = "") {
			std::cout << msg << X << ", " << Y << std::endl;
		}

		inline void translateX(float x) { X += x; }
		inline void translateY(float y) { Y += y; }
		inline void translate(Vector2D v) { X += v.X; Y += v.Y; }
};

#endif 

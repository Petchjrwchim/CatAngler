#pragma once

#include "SDL.h"
#include "Point.h"
#include "Vector2D.h"
#include "Engine.h"


class Camera
{
	public:
		
		void update(float dt);
		inline static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }
		inline SDL_Rect getViewBox() { return m_ViewBox; }
		inline Vector2D getPosition() { return m_Position; }
		inline void setTarget(Point* target) { m_Target = target; }

	private:
		Camera() {m_ViewBox = {0,0, SCREEN_WIDTH,SCREEN_HEIGHT};}
		Point* m_Target;
		Vector2D m_Position;

		SDL_Rect m_ViewBox;

		static Camera* s_Instance;

};


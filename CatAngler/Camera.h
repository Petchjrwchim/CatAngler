#pragma once

#include "SDL.h"
#include "Point.h"
#include "Vector2D.h"
#include "Engine.h"


class Camera
{
	public:
		
		void update(float dt);
		inline int GetSceneWidth() { return m_SceneWidth; }
		inline int GetSceneLength() { return m_SceneHeight; }

		inline static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }
		
		inline SDL_Rect getViewBox() { return m_ViewBox; }
		inline Vector2D getPosition() { return m_Position; }
		
		inline void moveX(float x) { m_Position.X = x; }
		inline void moveY(float y) { m_Position.Y = y; }

		inline void setTarget(Point* target) { m_Target = target; }
		inline void setSceneLimit(int w, int h) { m_SceneWidth = w; m_SceneHeight = h; }

	private:
		Camera();
		Point* m_Target;
		Vector2D m_Position;
		SDL_Rect m_ViewBox;
		static Camera* s_Instance;
		int m_SceneWidth, m_SceneHeight;

};


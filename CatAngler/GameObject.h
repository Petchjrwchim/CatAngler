#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"
#include "Transform.h"
#include "Point.h"
#include "SDL.h"

struct Properties {

	public:

		int Width, Height;
		std::string TextureID;
		float X, Y;
		SDL_RendererFlip FLip;

		Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) {
			X = x;
			Y = y;
			FLip = flip;
			Width = width;
			Height = height;
			TextureID = textureID;
			} 
		
};

class GameObject: public IObject
{
	public:

		GameObject() {}

		GameObject(Properties* props): m_TextureID(props->TextureID), m_Width(props->Width), m_Height(props->Height), m_FLip(props->FLip) {
		
			m_Transform = new Transform(props->X, props->Y);
			float px = (props->X + props->Width / 2);
			float py = (props->Y + props->Height / 2);
			m_Origin = new Point(px,py);
		}
		inline Point* getOrigin() { return m_Origin; }

		virtual void draw() = 0;
		virtual void update(float dt) = 0;
		virtual void clean() = 0;
	
	protected:
		Point* m_Origin;
		Transform* m_Transform;
		int m_Width, m_Height;
		std::string m_TextureID;
		SDL_RendererFlip m_FLip;
};

#endif
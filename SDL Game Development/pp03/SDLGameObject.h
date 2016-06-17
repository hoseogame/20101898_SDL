#pragma once
#include<string>
#include"Vector2D.h"
#include"GameObject.h"
#include "game.h"
#include "TextureManager.h"


class SDLGameObject : public GameObject
{
public:

	SDLGameObject( const LoadParams* pParams );
	
	SDLGameObject()
	{
	}
	virtual void draw();

	virtual void update();

	virtual void clean();

	virtual void load(const LoadParams* pParams);

protected:


	Vector2D m_position;

	Vector2D m_velocity;

	Vector2D m_acceleration;

	int m_width;

	int m_height;

	int m_currentRow;

	int m_currentFrame;
	int m_numFrames;

	std::string m_textureID;
};


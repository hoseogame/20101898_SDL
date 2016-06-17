#pragma once
#include<string>
#include"GameObject.h"
#include<vector>

class GameState
{
public:

	virtual void update() = 0;
	
	virtual void update2()
	{
	}

	virtual void render() = 0;

	virtual bool onEnter() = 0;

	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;
	
	std::vector<GameObject*> m_gameObjects;
	std::vector<std::string> m_textureIDList;

	virtual ~GameState()
	{
	}

protected:

};


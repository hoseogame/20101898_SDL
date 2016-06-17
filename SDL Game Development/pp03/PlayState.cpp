#include<iostream>
#include "PlayState.h"
#include"TextureManager.h"
#include"game.h"
#include"Player.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()

{

	for ( int i = 0; i < m_gameObjects.size(); i++ )

	{
		m_gameObjects[i]->update();

	}

}

void PlayState::render()

{

	for ( int i = 0; i < m_gameObjects.size(); i++ )

	{
		m_gameObjects[i]->draw();

	}

}

bool PlayState::onEnter()

{
	if(!TextureManager::Instance()->load("assets/helicopter.png", "helicopter",
		game::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* player = new Player(
		new LoadParams(100, 100, 400, 100, "helicopter"));

	m_gameObjects.push_back(player);

	return true;

}

bool PlayState::onExit()

{
	for(int i = 0; i < m_gameObjects.size(); i++)

	{
		
		delete m_gameObjects[i];

	}

	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("helicopter");

	return true;


}
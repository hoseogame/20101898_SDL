#include "DWPlayState.h"
#include<iostream>
#include"DWVideo.h"
#include"TextureManager.h"
#include"game.h"
#include"MenuButton.h"
#include"StateParser.h"
#include"MenuState.h"

const std::string DWPlayState::s_menuID = "PLAY";

DWPlayState::DWPlayState(void)
{
	m_callbacks.push_back(s_menuToMenu);
}


void DWPlayState::s_menuToMenu()

{
	if(!game::Instance()->getStateMachine()
		->changeState("MENU"))
	{
		game::Instance()->getStateMachine()->pushState(new MenuState());
		game::Instance()->getStateMachine()->changeState("MENU");
	}

}


void DWPlayState::update()

{
	for ( int i = 0; i < m_gameObjects.size(); i++ )

	{
		m_gameObjects[i]->update();

	}

}

void DWPlayState::update2()

{
	for ( int i = 0; i < m_gameObjects.size(); i++ )

	{
		m_gameObjects[i]->update2();

	}

}
void DWPlayState::setCallBacks(const std::vector<Callback>&callbacks)
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* temp_button = 
				dynamic_cast<MenuButton*>(m_gameObjects[i]);
			temp_button->setCallback(callbacks[temp_button->getCallBackID()]);
		}

	}
}

void DWPlayState::render()

{

	for ( int i = 0; i < m_gameObjects.size(); i++ )

	{
		m_gameObjects[i]->draw();

	}

}

bool DWPlayState::onEnter()

{

	StateParser parser;

	parser.parseState("assets/xml/play.xml",s_menuID,
		&m_gameObjects,&m_textureIDList);

	setCallBacks(m_callbacks);

	return true;

}

bool DWPlayState::onExit()

{

	std::cout << "exiting MenuState\n";
	for ( int i = 0; i < m_gameObjects.size(); i++ )

	{
		delete m_gameObjects[i];
	}

	m_gameObjects.clear();
	

	for ( int i = 0; i < m_textureIDList.size(); i++ )

	{
		TheTextureManager::Instance()
		->clearFromTextureMap(m_textureIDList[i]);
	}
	
	m_textureIDList.clear();

	return true;

}


DWPlayState::~DWPlayState()
{
	for ( int i = 0; i < m_gameObjects.size(); i++ )

	{
		delete m_gameObjects[i];
	}

	m_gameObjects.clear();
	

	for ( int i = 0; i < m_textureIDList.size(); i++ )

	{
		TheTextureManager::Instance()
		->clearFromTextureMap(m_textureIDList[i]);
	}
	
	m_textureIDList.clear();
}
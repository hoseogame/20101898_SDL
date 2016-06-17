#include<iostream>
#include"DWVideo.h"
#include "MenuState.h"
#include"TextureManager.h"
#include"game.h"
#include"MenuButton.h"
#include"StateParser.h"
#include"DWPlayState.h"

const std::string MenuState::s_menuID = "MENU";

MenuState::MenuState()
{
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);
}


void MenuState::s_menuToPlay()

{
	if(!game::Instance()->getStateMachine()
		->changeState("PLAY"))
	{
		game::Instance()->getStateMachine()->pushState(new DWPlayState());
		game::Instance()->getStateMachine()->changeState("PLAY");
	}

}

void MenuState::s_exitFromMenu()

{
	game::Instance()->quit();

}

void MenuState::update()

{
	for ( int i = 0; i < m_gameObjects.size(); i++ )

	{
		m_gameObjects[i]->update();

	}

}

void MenuState::update2()

{
	for ( int i = 0; i < m_gameObjects.size(); i++ )

	{
		m_gameObjects[i]->update2();

	}

}
void MenuState::setCallBacks(const std::vector<Callback>&callbacks)
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

void MenuState::render()

{

	for ( int i = 0; i < m_gameObjects.size(); i++ )

	{
		m_gameObjects[i]->draw();

	}

}

bool MenuState::onEnter()

{

	StateParser parser;

	parser.parseState("assets/xml/main.xml",s_menuID,
		&m_gameObjects,&m_textureIDList);

	setCallBacks(m_callbacks);

	return true;

}

bool MenuState::onExit()

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


MenuState::~MenuState()
{
	for ( int i = 0; i < m_gameObjects.size(); i++ )

	{
		delete m_gameObjects[i];
	}
}
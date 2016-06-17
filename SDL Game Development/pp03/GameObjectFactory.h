#pragma once
#include<string>
#include<iostream>
#include"BaseCreator.h"
class GameObjectFactory
{
public:
	static GameObjectFactory* Instance();
	bool registerType(std::string typeID, BaseCreator* pCreator)
	{
		std::map<std::string, BaseCreator*>::iterator it = 
			m_creators.find(typeID);

		if(it != m_creators.end())
		{
			delete pCreator;
			return false;
		}
		m_creators[typeID] = pCreator;
		return true;
	}

	GameObject* create(std::string typeID)
	{
		std::map<std::string, BaseCreator*>::iterator it = 
			m_creators.find(typeID);

		if( it == m_creators.end())
		{
			std::cout<<"not find : " <<typeID<<"\n";
			return NULL;
		}
		BaseCreator* pCreator = (*it).second;
		return pCreator->createGameObject();

	}

	~GameObjectFactory();
private:

	GameObjectFactory()
	{
	}
	
	static GameObjectFactory* s_pInstance;
	std::map<std::string, BaseCreator*> m_creators;
};


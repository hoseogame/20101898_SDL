#include "GameObjectFactory.h"


GameObjectFactory* GameObjectFactory::s_pInstance = 0;

GameObjectFactory* GameObjectFactory::Instance()

{

	if ( s_pInstance == 0 )

	{

		s_pInstance = new GameObjectFactory();

		return s_pInstance;

	}

	return s_pInstance;

}
GameObjectFactory::~GameObjectFactory()
{
	for(std::map<std::string, BaseCreator*>::iterator it  = m_creators.begin();
										it != m_creators.end();it++)
	{
		delete it->second;
	}

	m_creators.clear();
}

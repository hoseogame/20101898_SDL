#include "StateParser.h"
#include "TextureManager.h"
#include "game.h"
#include "GameObjectFactory.h"

StateParser::~StateParser(void)
{
}

bool StateParser::parseState(const char*stateFile, std::string stateId,
							 std::vector<GameObject*>*pObjects,
							 std::vector<std::string> *pTextureIDs)
{
	TiXmlDocument xmlDoc;
	if(!xmlDoc.LoadFile(stateFile))
	{
		return false;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	TiXmlElement* pStateRoot = 0;

	for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement())
	{
		if(e->Value() == stateId)
		{
			pStateRoot = e;
		}
	}
	
	for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement())
	{

		//텍스쳐 읽어옴
		if(e->Value() == std::string("TEXTURES"))
		{
			parseTextures(e,pTextureIDs);
		}

		if(e->Value() == std::string("OBJECTS"))
		{
			parseObjects(e,pObjects);
		}
	}

	return true;
}

void StateParser::parseTextures
		(TiXmlElement* pStateRoot, std::vector<std::string>*pTextureIDs)
{
	for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement())
	{
		std::string file_name = e->Attribute("filename");
		std::string id = e->Attribute("ID");
		pTextureIDs->push_back(id);
		TextureManager::Instance()->load(file_name,id,game::Instance()->getRenderer());
	}
}

void StateParser::parseObjects
		(TiXmlElement* pStateRoot,std::vector<GameObject*>*pObjects)
{
	for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement())
	{
		int x,y,width, height, numFrames,callbackID,animSpeed;
		std::string textureID;
		e->Attribute("x",&x);
		e->Attribute("y",&y);
		e->Attribute("width",&width);
		e->Attribute("height",&height);
		e->Attribute("numFrames",&numFrames);
		e->Attribute("callbackID",&callbackID);
		e->Attribute("animSpeed",&animSpeed);
		textureID = e->Attribute("textureID");

		GameObject * pGameObject =
			GameObjectFactory::Instance()->create(e->Attribute("type"));

		pGameObject->load(new LoadParams(x,y,width, height,textureID, numFrames,callbackID,animSpeed));

		pObjects->push_back(pGameObject);

	}

}

	
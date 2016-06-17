#pragma once

#include<iostream>
#include<vector>
#include<string>
#include"tinyxml.h"

class GameObject;

class StateParser
{
public:
	bool parseState(const char*stateFile, std::string stateId,
		std::vector<GameObject*>*pObjects,
		std::vector<std::string> *pTextureIDs);
	~StateParser(void);

private:
	void parseObjects
		(TiXmlElement* pStateRoot,std::vector<GameObject*>*pObjects);
	void parseTextures
		(TiXmlElement* pStateRoot, std::vector<std::string>*pTextureIDs);
};


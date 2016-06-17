#pragma once

#include<string>
#include<map>
#include"GameObject.h"

class BaseCreator
{
public :
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {};
};
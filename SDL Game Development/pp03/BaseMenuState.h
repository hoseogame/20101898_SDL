#pragma once
#include "GameState.h"

class BaseMenuState :
	public GameState
{

protected:
	typedef void (*Callback)();
	virtual void setCallBacks(const std::vector<Callback>&callbacks) = 0;
	std::vector<Callback> m_callbacks;

};


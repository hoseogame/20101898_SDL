#pragma once
#include "SDL.h"
class DWTime
{
public:

	static DWTime* Instance();

	void SetTime(Uint32 tick);
	Uint32 GetTime ();
	Uint32 GetDeltaTime ();
	
	~DWTime();
private: 
	Uint32 time;
	Uint32 delta_time;
	static DWTime* s_pInstance;
	DWTime();
};


#include "DWTime.h"

DWTime* DWTime::s_pInstance = 0;


DWTime* DWTime::Instance()

{

	if (s_pInstance == 0)

	{

		s_pInstance = new DWTime();

		return s_pInstance;

	}

	return s_pInstance;

}


DWTime::DWTime() : delta_time(0),time(0)
{
}


DWTime::~DWTime()
{
}

void DWTime::SetTime(Uint32 tick)
{
	delta_time = tick - time;
	time = tick;
}
Uint32 DWTime::GetDeltaTime ()
{
	return delta_time;
}

Uint32 DWTime::GetTime ()
{
	return time;
}
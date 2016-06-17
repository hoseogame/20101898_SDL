#pragma once

#include <string>
#include "SDL.h"
#include "LoadParams.h"


class GameObject
{
public:

	virtual void draw() = 0;

	virtual void update() = 0;
	virtual void update2() 
	{
	};

	virtual void clean() = 0;

	virtual void load(const LoadParams* pParams)=0;
	
	
	const LoadParams* first_set_params;
	
	GameObject()
	{
	}

	virtual ~GameObject() 
	{
		delete first_set_params;
	}

protected:

	GameObject( const LoadParams* pParams ) : first_set_params(pParams)
	{}

	

};


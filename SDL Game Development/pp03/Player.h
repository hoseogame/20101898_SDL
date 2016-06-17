#pragma once
#include "SDLGameObject.h"
#include "BaseCreator.h"


class Player :
	public SDLGameObject
{
public:
	
	 Player( const LoadParams* pParams );
	 
	 Player()
	 {
	 }

	   virtual void draw();

	   virtual void update();

	   virtual void clean(); 
	   
	virtual void load(const LoadParams* pParams);
	   
private:
	   void handleInput();
};


class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};
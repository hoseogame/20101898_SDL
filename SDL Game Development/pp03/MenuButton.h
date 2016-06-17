#pragma once

#include "SDLGameObject.h"
#include "LoadParams.h"
#include "BaseCreator.h"

enum button_state

{

	MOUSE_OUT = 0,

	MOUSE_OVER = 1,

	CLICKED = 2

};

class MenuButton :
	public SDLGameObject
{
public:
	~MenuButton();
	
	MenuButton( const LoadParams* pParams );
	MenuButton( const LoadParams* pParams, void ( *callback )() );
	MenuButton()
	{
	}

	virtual void draw();

	virtual void update();

	virtual void clean();

	virtual void load(const LoadParams* pParams);

	void ( *m_callback )();
	void setCallback(void(*callback)())
	{
		m_callback = callback;
	}

	int getCallBackID()
	{
		return m_callbackID;
	}
	bool m_bReleased;

private:
	int m_callbackID;

};

class ButtonCreator : public BaseCreator
{
public:
	virtual GameObject* createGameObject() const
	{
		return new MenuButton();
	}
};


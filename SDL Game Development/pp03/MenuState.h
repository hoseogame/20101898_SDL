#pragma once
#include "BaseMenuState.h"
class MenuState :
	public BaseMenuState
{
public:
	MenuState();
	~MenuState();
	virtual void update();

	virtual void render();

	virtual bool onEnter();
	
	virtual void update2();

	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }
	
	virtual void setCallBacks(const std::vector<Callback>&callbacks);

private:

	static void s_menuToPlay();
	static void s_exitFromMenu();

	static const std::string s_menuID;
};


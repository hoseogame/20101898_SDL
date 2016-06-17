#pragma once
#include "basemenustate.h"
class DWPlayState :
	public BaseMenuState
{
public:
	DWPlayState(void);
	~DWPlayState(void);

	virtual void update();

	virtual void render();

	virtual bool onEnter();
	
	virtual void update2();

	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }
	
	virtual void setCallBacks(const std::vector<Callback>&callbacks);

private:

	static void s_menuToMenu();

	static const std::string s_menuID;
};


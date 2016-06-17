#pragma once
#include "GameState.h"
#include  <vector>
#include <string>
class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	void pushState( GameState* pState );

	bool changeState(std::string state_name);
	
	void render();

	void popState();

	void update();
	void update2();


protected:
	std::vector<GameState*> state_list;
	GameState* run_state;
	GameState* temp_exit_state;
	bool on_state_change;


};


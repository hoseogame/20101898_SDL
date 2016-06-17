#include "GameStateMachine.h"



GameStateMachine::GameStateMachine():
	run_state( nullptr ),on_state_change(false)
{
}


GameStateMachine::~GameStateMachine()
{

	for ( std::vector<GameState*>::const_iterator iter = state_list.begin();
		iter != state_list.end(); ++iter )
	{
		delete(*iter);
	}
	state_list.clear();
}

void GameStateMachine::update()
{
	if ( run_state != nullptr )
	{
		run_state->update();
	}

}

void GameStateMachine::update2()
{

	if ( run_state != nullptr )
	{
		run_state->update2();
	}
}

void GameStateMachine::render()
{
	if ( run_state != nullptr )
	{
		run_state->render();
	}
	
	if(on_state_change)
	{
		run_state->onExit();
		run_state = temp_exit_state;
		run_state->onEnter();
		on_state_change = false;
	}

}
void GameStateMachine::pushState( GameState* pState )
{
	state_list.push_back( pState );
	
	if ( run_state == nullptr )
	{
		run_state = pState;
		run_state->onEnter();
	}
}

bool GameStateMachine::changeState(std::string state_name)
{
	if ( !state_list.empty() )
	{
		for ( std::vector<GameState*>::const_iterator iter = state_list.begin();
			iter != state_list.end(); ++iter )
		{
			if ( (*iter)->getStateID() == state_name )
			{
				//���� ������Ʈ�� �� ��Ű�� ���ο� ������Ʈ�� �� ��Ų��.

				temp_exit_state = (*iter);
				on_state_change = true;

				return true;
			}
		}
	}
	return false;
	
}

//���� ������Ʈ�� ���� �ش�
void GameStateMachine::popState()
{
	if ( !state_list.empty() )
	{
		for ( std::vector<GameState*>::const_iterator iter = state_list.begin();
			iter != state_list.end(); ++iter )
		{
			if ( (*iter)->getStateID() == run_state->getStateID() )
			{
				std::vector<GameState*>::const_iterator temp_iter = iter;

				run_state->onExit();
				delete(run_state);
				if ( iter == state_list.begin() )
				{
					run_state = nullptr;
					state_list.erase( temp_iter );
					return;
				}

				--iter;
				run_state = (*iter);
				state_list.erase( temp_iter );

				return;
			}
			
		}
	}
}
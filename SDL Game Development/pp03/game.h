#pragma once
#include "SDL.h"
#include <vector>
#include "GameStateMachine.h"

class GameObject;

class game
{

public:
	static game* Instance();
	/*
	game(): m_bRunning (true), speed(100){}

	~game() {}
	*/
	bool init( const char* title, int xpos, int ypos,

		int width, int height, bool fullscreen );

	void render();

	void update();

	void update2();

	void handleEvents();

	void clean();

	void quit()
	{
		m_bRunning = false;
	}

	bool running() { return m_bRunning; }

	int m_currentFrame;

	GameStateMachine* getStateMachine(){ return m_pGameStateMachine; }
	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	SDL_Window* getWindow() const { return m_pWindow; }

private:

	game() : m_bRunning(true)
	{

	}

	// create the s_pInstance member variable

	static game* s_pInstance;

	// create the typedef

	GameStateMachine* m_pGameStateMachine;
	
	SDL_Window* m_pWindow;

	SDL_Renderer* m_pRenderer;
	/*
	GameObject m_go;

	Player m_player;
	*/
	bool m_bRunning;
	int speed;


	GameObject* m_go;

	GameObject* m_player;

	GameObject* m_enemy;
};
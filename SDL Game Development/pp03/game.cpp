#include<SDL_image.h>
#include "game.h"
#include"Enemy.h"
#include"Player.h"
#include"GameObject.h"
#include"TextureManager.h"
#include"LoadParams.h"
#include"InputHandler.h"
#include"MenuState.h"
#include"GameObjectFactory.h"
#include"MenuButton.h"
#include"DWVideo.h"

game* game::s_pInstance = 0;


game* game::Instance()

{

	if ( s_pInstance == 0 )

	{

		s_pInstance = new game();

		return s_pInstance;

	}

	return s_pInstance;

}

bool game::init( const char* title, int xpos, int ypos,

	int width, int height, bool fullscreen )

{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) >= 0 )

	{

		m_pWindow = SDL_CreateWindow( title, xpos, ypos,

			width, height, SDL_WINDOW_SHOWN );

		if ( m_pWindow != 0 )

		{
			GameObjectFactory::Instance()->registerType("MenuButton",new ButtonCreator());
			GameObjectFactory::Instance()->registerType("Video",new VideoCreator());

			m_pRenderer = SDL_CreateRenderer( m_pWindow, -1, 0 );
			m_pGameStateMachine = new GameStateMachine();
			m_pGameStateMachine->pushState( new MenuState() );

		}

	}
	else {

		return false; // sdl could not initialize

	}

	return true;

}


void game::update()
{
	m_pGameStateMachine->update();
}
void game::update2()
{
	m_pGameStateMachine->update2();
}

void game::render()

{

	SDL_RenderClear( m_pRenderer ); // clear to the draw colour

	m_pGameStateMachine->render();

	SDL_RenderPresent( m_pRenderer ); // draw to the screen

	/*
	SDL_RenderClear(  m_pRenderer ); // draw color로 render 지우기

	TheTextureManager::Instance()->draw( "rider", 100, 0, 128, 82, m_pRenderer );
	
	TheTextureManager::Instance()->drawFrame( "dog", 0, 0, 128, 82, 1, m_currentFrame, m_pRenderer,0);
	TheTextureManager::Instance()->drawFrame( "dog1", 0, 100, 128, 82, 1, m_currentFrame, m_pRenderer,40 );

	m_go.draw( m_pRenderer );

	m_player.draw( m_pRenderer );

	SDL_RenderPresent( m_pRenderer );*/


}
void game::clean()
{

	delete m_pGameStateMachine;

	TheInputHandler::Instance()->clean();
	delete TextureManager::Instance();
	delete GameObjectFactory::Instance();

	SDL_DestroyWindow( m_pWindow );

	SDL_DestroyRenderer( m_pRenderer );

	SDL_Quit();


}
void game::handleEvents() {

	TheInputHandler::Instance()->update();
	SDL_Event event;

	if ( SDL_PollEvent( &event ) )

	{

		switch ( event.type ) {

		case SDL_QUIT:
		{
			m_bRunning = false;

			break;
		}
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{ 
			 case SDLK_ESCAPE:
			 {

				 m_bRunning = false;
				 break;
			 }
			 case SDLK_0:
			 {

				 speed +=10;
				 break;
			 }
			 case SDLK_1:
			 {

				 speed -= 10;
				 break;
			 }
			 break;
			}


		}

		default:

			break;

		}

	}
}
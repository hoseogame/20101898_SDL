#include "InputHandler.h"
#include "game.h"
#include "Vector2D.h"

InputHandler* InputHandler::s_pInstance = 0;


InputHandler::InputHandler()

{
	for ( int i = 0; i < 3; i++ )

	{
		m_mouseButtonStates.push_back( false );

	}
	m_mousePosition = new Vector2D( 0, 0 );
	// 생성자

}

bool InputHandler::getMouseButtonState(mouse_buttons get_state )
{
	return m_mouseButtonStates[get_state];
}

void InputHandler::clean()

{
	delete s_pInstance;
	// 향후 추가

}

Vector2D InputHandler::getMousePosition()
{
	int temp_x, temp_y;
	SDL_GetMouseState(&temp_x,&temp_y);
	m_mousePosition->setX(temp_x);
	m_mousePosition->setY(temp_y);
	return *m_mousePosition;
}

bool InputHandler::isKeyDown( SDL_Scancode key )

{

	if ( m_keystates != 0 )
	{

		if ( m_keystates[key] == 1 )
		{
			return true;
		}
		else 
		{
			return false;
		}

	}

	return false;

}

void InputHandler::update()

{

	SDL_Event event;

	while ( SDL_PollEvent( &event ) )

	{

		if ( event.type == SDL_QUIT )

		{

			game::Instance()->quit();

		}else if ( event.type == SDL_KEYUP )

		{

			m_keystates = SDL_GetKeyboardState( 0 );

		}

		else if ( event.type == SDL_KEYDOWN )

		{

			m_keystates = SDL_GetKeyboardState( 0 );

		}

		if ( event.type == SDL_MOUSEMOTION )

		{

			m_mousePosition->setX( event.motion.x );

			m_mousePosition->setY( event.motion.y );

		}
		else if ( event.type == SDL_MOUSEBUTTONDOWN )
		{//마우스클릭구현할것
			m_mouseButtonStates[event.button.button-1] = true;
		}
		else if(event.type == SDL_MOUSEBUTTONUP)
		{
			m_mouseButtonStates[event.button.button-1] = false;
		}

	}

}

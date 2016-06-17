#include "Player.h"
#include "InputHandler.h"

Player::Player( const LoadParams* pParams ) : SDLGameObject

	( pParams )

{

}

void Player::handleInput()

{


	Vector2D target = InputHandler::Instance()->getMousePosition();

	m_velocity = target - m_position;

	m_velocity /= 50;

}
void Player::draw()

{
	if(m_velocity.getX() > 0)

	{

		TextureManager::Instance()->drawFrame(m_textureID,

			(Uint32)m_position.getX(), (Uint32)m_position.getY(),

			m_width, m_height, m_currentRow, m_currentFrame,

			game::Instance()->getRenderer(),

			SDL_FLIP_HORIZONTAL);

	} else
	{
	}

}

void Player::update()

{
	m_velocity.setX( 0 );

	m_velocity.setY( 0 );

	handleInput(); // add our function

	m_currentFrame = int( ((SDL_GetTicks() / 100) % 6) );

	SDLGameObject::update();
	/*	m_currentFrame = int( ((SDL_GetTicks() / 100) % 6) );

	m_acceleration.setX( 1 );

	SDLGameObject::update();*/

}

void Player::clean()

{
	delete this;
}



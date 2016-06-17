#include "SDLGameObject.h"

SDLGameObject::SDLGameObject( const LoadParams* pParams ) :

	GameObject( pParams ),
	m_position( pParams->getX(), pParams->getY() ),
	m_velocity( 0.0f, 0.0f ),
	m_acceleration( 0.0f, 0.0f )

{


	m_width = pParams->getWidth();

	m_height = pParams->getHeight();

	m_textureID = pParams->getTextureID();

	m_currentRow = 1;

	m_currentFrame = 1;
	
	m_numFrames = pParams->getNumFrames();

}

void SDLGameObject::update()

{

	m_velocity += m_acceleration;

	m_position += m_velocity;

}
void SDLGameObject::draw()

{
	TextureManager::Instance()->drawFrame( m_textureID,

		(int)m_position.getX(), (int)m_position.getY(),

		m_width, m_height, m_currentRow, m_currentFrame,

		game::Instance()->getRenderer(),0 );

}

void SDLGameObject::load(const LoadParams* pParams)
{
	first_set_params = pParams;

	m_position = Vector2D( pParams->getX(), pParams->getY() );

	m_velocity = Vector2D( 0.0f, 0.0f );

	m_acceleration = Vector2D( 0.0f, 0.0f );

	m_width = pParams->getWidth();

	m_height = pParams->getHeight();

	m_textureID = pParams->getTextureID();

	m_currentRow = 1;

	m_currentFrame = 1;

	m_numFrames = pParams->getNumFrames();
	
}

void SDLGameObject::clean()
{
}
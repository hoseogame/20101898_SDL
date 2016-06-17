#include "TextureManager.h"
#include<SDL_image.h>

TextureManager* TextureManager::s_pInstance = NULL;

TextureManager::~TextureManager()
{
	for(std::map<std::string, SDL_Texture*>::iterator it  = texture_map.begin();
										it != texture_map.end();it++)
	{
		SDL_DestroyTexture(it->second);
	}

	texture_map.clear();
}

bool TextureManager::load( std::string fileName, std::string id,
						  SDL_Renderer* pRenderer )
{
	SDL_Surface* temp_surface = IMG_Load( fileName.c_str() );

	if ( temp_surface == 0 )
	{
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface( pRenderer, temp_surface );
	SDL_FreeSurface( temp_surface );

	if ( texture != 0 )
	{
		texture_map[id] = texture;
		return true;
	}

	return false;

}

void TextureManager::draw( std::string id, int x, int y, int width,
						  int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.w /= 2;
	destRect.h /= 2;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx( pRenderer, texture_map[id], &srcRect, &destRect, 0, 0, flip );


}

void TextureManager::drawFrame( std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
							   SDL_Renderer* pRenderer, int angle, SDL_RendererFlip flip )
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.h = destRect.h = height;
	srcRect.w = destRect.w = width;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx( pRenderer, texture_map[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawVideo(SDL_Texture * texture,int x, int y, int width, int height,
							   SDL_Renderer* pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopy(pRenderer,texture,&srcRect,&destRect);
}

void TextureManager::clearFromTextureMap( std::string id )

{
	SDL_DestroyTexture(texture_map[id]);
	texture_map.erase( id );

}
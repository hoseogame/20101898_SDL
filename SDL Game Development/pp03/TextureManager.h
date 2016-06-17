#pragma once
#include "SDL.h"
#include<map>
#include<string>
class TextureManager
{
private:

	static TextureManager* s_pInstance;
	TextureManager() 
	{}


public:

	static TextureManager* Instance()
	{
		if ( s_pInstance == NULL )
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	~TextureManager();

	std::map<std::string, SDL_Texture*> texture_map;

	bool load( std::string fileName, std::string id,
		SDL_Renderer* pRenderer );

	void draw( std::string id, int x, int y, int width,
		int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE );

	void drawFrame( std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
		SDL_Renderer* pRenderer, int angle, SDL_RendererFlip flip = SDL_FLIP_NONE );

	void drawVideo(SDL_Texture * texture,int x, int y, int width, int height, SDL_Renderer* pRenderer);

	void clearFromTextureMap( std::string id );
};


typedef TextureManager TheTextureManager;
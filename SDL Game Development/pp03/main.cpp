#include"game.h"
#include"ffmpegH.h"
#include"DWTime.h"
#include<iostream>

game* g_game = 0; // our Game object

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;
int main( int argc, char* argv[] )

{
	Uint32 frameStart, frameTime, save_time = 0;

	std::cout << "game init attempt...\n";
	
	av_register_all();

	if ( game::Instance()->init( "Chapter 1", 100, 100, 640, 480, false ) )
	{

		std::cout << "game init success!\n";

		
		frameStart = SDL_GetTicks();
		while ( game::Instance()->running() )

		{
			DWTime::Instance()->SetTime(SDL_GetTicks());
			save_time += DWTime::Instance()->GetDeltaTime();
			if(save_time > DELAY_TIME)
			{
				
				game::Instance()->handleEvents();

				game::Instance()->update();


				save_time = 0;
				frameStart = SDL_GetTicks();

			}

			game::Instance()->update2();
			game::Instance()->render();


		}
	}

	else {

		std::cout << "game init failure - " << SDL_GetError() << "\n";


		std::cout << "game closing...\n";

		game::Instance()->clean();

		return -1;


	}
		game::Instance()->clean();
		delete DWTime::Instance();

		return 0;
}
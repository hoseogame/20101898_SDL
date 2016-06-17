#pragma once
#include "SDL.h"
#include <vector>

class Vector2D;

enum mouse_buttons

{

	LEFT = 0,

	MIDDLE = 1,

	RIGHT = 2

};
class InputHandler
{
public:

	static InputHandler* Instance()

	{

		if ( s_pInstance == 0 ) {

			s_pInstance = new InputHandler();

		}

		return s_pInstance;

	}

	void update();
	bool isKeyDown( SDL_Scancode key );

	bool getMouseButtonState(mouse_buttons get_state );
	Vector2D getMousePosition();

	void clean(); // 디바이스 관련 초기화된 부분을 clear
	// mouse buttion events
	std::vector<bool> m_mouseButtonStates;
	// mouse motion event
	Vector2D* m_mousePosition;

private:

	InputHandler();

	~InputHandler()
	{
		delete m_mousePosition;
	}
	const Uint8* m_keystates;
	static InputHandler* s_pInstance;


};

typedef InputHandler TheInputHandler;

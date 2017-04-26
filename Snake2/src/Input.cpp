///////////////////////
// Input implementation
///////////////////////
#include "Input.h"

bool Input::getInput()
{
	bool result = SDL_PollEvent(eventPtr);

	_quit = eventPtr->type == SDL_QUIT;
	_keyLeft = eventPtr->key.keysym.sym == SDLK_LEFT;
	_keyRight = eventPtr->key.keysym.sym == SDLK_RIGHT;
	_keyUp = eventPtr->key.keysym.sym == SDLK_UP;
	_keyDown = eventPtr->key.keysym.sym == SDLK_DOWN;
	_keyEsc = eventPtr->key.keysym.sym == SDLK_ESCAPE;
	_keyEnter = eventPtr->key.keysym.sym == SDLK_RETURN;

	return result;
}

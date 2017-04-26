#pragma once
//////////////////////////////
// Input handler for sdl event
//////////////////////////////
//#include <memory>
#include "SDL.h"

class Input
{
public:
	explicit Input(SDL_Event *e) :
		eventPtr(e),
		_keyLeft(false),
		_keyRight(false),
		_keyUp(false),
		_keyDown(false),
		_keyEsc(false),
		_keyEnter(false),
		_quit(false)
	{}
	~Input() { delete eventPtr; }

	//update input
	bool getInput();
	//keys
	bool Left() const { return _keyLeft; }
	bool Right() const { return _keyRight; }
	bool Up() const { return _keyUp; }
	bool Down() const { return _keyDown; }
	bool Esc() const { return _keyEsc; }
	bool Valid() const { return _keyEnter; }
	bool Quit() const { return _quit; }

private:
	bool _keyLeft;
	bool _keyRight;
	bool _keyUp;
	bool _keyDown;
	bool _keyEsc;
	bool _keyEnter;
	bool _quit;
	SDL_Event *eventPtr;
};
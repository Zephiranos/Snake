#pragma once
/////////////////////////
// Handler for sdl_window
/////////////////////////
#include "SDL.h"
#include "Renderer.h"

class Window
{
public:
	explicit Window(SDL_Window *w) : windowPtr(w) {}
	~Window();

	//copy
	Window(Window &w);
	Window& operator=(Window &w);

	//Utility
	void Destroy() { SDL_DestroyWindow(windowPtr); }
	bool isNull() { return windowPtr == nullptr; }

	//int getWidth() { SDL_GetWindowSurface(windowPtr)->w; }
	//int getHeight() { SDL_GetWindowSurface(windowPtr)->h; }

	Renderer createRenderer();

private:
	SDL_Window *windowPtr;
};
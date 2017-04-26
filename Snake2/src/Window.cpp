//////////////////////////
// Window implementation
//////////////////////////
#include "Window.h"

Window::Window(Window &w) :
	windowPtr(w.windowPtr)
{
}

Window::~Window()
{
	//if (windowPtr != nullptr) Destroy();
	windowPtr = NULL;
}

Window& Window::operator=(Window &w)
{
	windowPtr = w.windowPtr;
	return *this;
}

Renderer Window::createRenderer()
{
	return Renderer(SDL_CreateRenderer(windowPtr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
}
#pragma once
/////////////////////////////////
// Texture wrapper for SDLTexture
/////////////////////////////////
#include "SDL.h"

class Texture
{
public:
	Texture(SDL_Texture *t) : txturePtr(t) {}
	~Texture() { txturePtr = nullptr; }

	SDL_Texture* get() { return txturePtr; }
private:
	SDL_Texture *txturePtr;
};
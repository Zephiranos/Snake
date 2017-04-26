#pragma once
#pragma once
///
// Render handler for sdl renderer
///
#include "SDL.h"
#include <string>
#include "Texture.h"

class Renderer
{
public:
	explicit Renderer(SDL_Renderer * r) : rendererPtr(r) {}
	~Renderer();

	//Copy
	Renderer(Renderer &w);
	Renderer& operator=(Renderer &w);

	//Utility
	void Destroy() { SDL_DestroyRenderer(rendererPtr); }
	bool isNull() { return rendererPtr == nullptr; }

	//rendering functions
	void clearScreen(int r = 0, int g = 0, int b = 0, int a = 255);
	void changeColor(int r = 0, int g = 0, int b = 0, int a = 255);
	void renderRect(const SDL_Rect *sdlr);
	void renderScene();
	Texture* renderTxtToTexture(const std::string text, const std::string fontFile, const SDL_Color color, int fontsize);
	void renderTexture(Texture *t, const SDL_Rect *sdlr);

private:
	SDL_Renderer *rendererPtr;
};
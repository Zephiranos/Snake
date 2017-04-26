//////////////////////////
// Renderer implementation
//////////////////////////
#include "Renderer.h"
#include "SDL_ttf.h"

Renderer::Renderer(Renderer &r) :
	rendererPtr(r.rendererPtr)
{
}

Renderer::~Renderer()
{
	//if (rendererPtr != nullptr) Destroy();
	rendererPtr = NULL;
}

Renderer& Renderer::operator=(Renderer &r)
{
	rendererPtr = r.rendererPtr;
	return *this;
}

void Renderer::clearScreen(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(rendererPtr, r, g, b, a);
	SDL_RenderClear(rendererPtr);
}

void Renderer::changeColor(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(rendererPtr, r, g, b, a);
}

void Renderer::renderRect(const SDL_Rect *sdlr)
{
	SDL_RenderFillRect(rendererPtr, sdlr);
}

void Renderer::renderScene()
{
	SDL_RenderPresent(rendererPtr);
}

Texture* Renderer::renderTxtToTexture(const std::string text, const std::string fontFile, const SDL_Color color, int fontsize)
{

	TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontsize);

	if (font == NULL) return NULL;

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

	Texture* textTexture = new Texture(SDL_CreateTextureFromSurface(rendererPtr, textSurface));

	SDL_FreeSurface(textSurface);

	TTF_CloseFont(font);

	return  textTexture;
}

void Renderer::renderTexture(Texture *t, const SDL_Rect *sdlr)
{
	SDL_RenderCopy(rendererPtr, t->get(), NULL, sdlr);
}
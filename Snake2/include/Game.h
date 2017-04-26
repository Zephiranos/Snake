#pragma once
///
// Game Class Header
///
#include "SDL.h"
#include "Input.h"
#include "Snake.h"
#include "Renderer.h"
#include "Window.h"

enum GameState
{
	Running,
	Stopped
};

class Game
{
public:
	Game(int mapW, int mapH, int windowW, int windowH);
	~Game();

	//game execution
	int Execute();
	void Stop();

private:

	int Init();

	void Event();
	void Update();
	void Render();

	void changeApplePos(int w, int h);
	void Loss();
	void Restart();

	bool _isRunning;
	GameState gs;

	Renderer _renderer;
	Window _window;

	Texture *_txtureLoss;
	Texture *_txtureScore;
	Texture *_txtureRetry1;
	Texture *_txtureRetry2;
	std::string _fontFile;
	SDL_Color _fontColor;

	Input _input;

	Snake *_snake;
	int _mapW, _mapH;
	int _appleX, _appleY;
	int _cubeW, _cubeH;
	int _windowW, _windowH;




};
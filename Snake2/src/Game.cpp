//////////////////////
// Game implementation
//////////////////////

#include "Game.h"
#include "SDL.h"
#include "SDL_ttf.h"

Game::Game(int mapW, int mapH, int windowW, int windowH):
	_input(new SDL_Event()),
	_snake(new Snake(1,1,4)),
	_mapW(mapW),
	_mapH(mapH),
	_cubeW((windowW - mapW + 1) / mapW),
	_cubeH((windowH - mapH + 1) / mapH),
	_windowW(windowW),
	_windowH(windowH),
	gs(GameState::Running),
	_window(nullptr),
	_renderer(nullptr),
	_txtureLoss(nullptr),
	_txtureRetry1(nullptr),
	_txtureRetry2(nullptr),
	_txtureScore(nullptr),
	_fontFile("../Snake2/Assets/Fonts/Gameplay.ttf"),
	_fontColor(SDL_Color{255,255,255,255}),
	_isRunning(true)
{
	if (Init() == -1) _isRunning = false;
	_appleX = mapW / 2 + (rand() % (int)(mapW - mapW / 2 + 1));
	_appleY = mapH / 2 + (rand() % (int)(mapH - mapH / 2 + 1));
}

Game::~Game()
{
	//SDL_DestroyWindow(_window);
	//SDL_DestroyRenderer(_renderer);
	_window.Destroy();
	_renderer.Destroy();
	delete _snake;
	SDL_Quit();
}

int Game::Execute()
{
	while (_isRunning) {
		Event();
		Update();
		Render();
	}
	return 0;
}

void Game::Stop()
{
	_isRunning = false;
}

int Game::Init()
{
	//SDL Initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		return -1;
	}

	//_window = SDL_CreateWindow("Snake", 100, 100, _windowW, _windowH, SDL_WINDOW_SHOWN);
	_window = Window(SDL_CreateWindow("Snake", 100, 100, 600, 600, SDL_WINDOW_SHOWN));
	if (_window.isNull())
	{
		return -1;
	}
	//_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	_renderer = _window.createRenderer();
	if (_renderer.isNull())
	{
		return -1;
	}

	//Font Initialization
	if (TTF_Init() != 0)
	{
		return -1;
	}

	_txtureLoss = _renderer.renderTxtToTexture("You Lost", _fontFile, _fontColor, 20);
	_txtureRetry1 = _renderer.renderTxtToTexture("Press Enter", _fontFile, _fontColor, 10);
	_txtureRetry2 = _renderer.renderTxtToTexture("to Restart", _fontFile, _fontColor, 10);

	return 0;
}

void Game::Event()
{
	while(_input.getInput())
	{
		//check game quit
		if (_input.Quit())
		{
			Stop();
			break;
		}
		//get user input
		//if (_input.Esc())
		//{
		//	//g.changeState(g.getMenuState());
		//}
		if (gs == Running)
		{
			if (_input.Down())
				_snake->moveVertical(1);
			if (_input.Up())
				_snake->moveVertical(-1);
			if (_input.Left())
				_snake->moveHorizontal(-1);
			if (_input.Right())
				_snake->moveHorizontal(1);
		}
		else if (gs == Stopped)
		{
			if (_input.Valid())
				Restart();
		}
	}
}

void Game::Update()
{
	if (gs == Running)
	{
		_snake->update();
		if (_snake->collideApple(_appleX, _appleY))
		{
			_snake->grow();
			changeApplePos(_mapW, _mapH);
		}
		if (_snake->collideSelfNWorld(_mapW, _mapH))
		{
			Loss();
		}
	}
}

void Game::Render()
{
	_renderer.clearScreen();

	//draw snake
	_renderer.changeColor(0,150,0);
	std::deque<std::pair<int, int> > body = _snake->getBody();
	for (auto cell : body)
	{
		SDL_Rect sdlr;
		sdlr.x = cell.first * (_cubeW + 1);
		sdlr.y = cell.second * (_cubeH + 1);
		sdlr.h = _cubeH;
		sdlr.w = _cubeW;
		_renderer.renderRect(&sdlr);
	}

	//draw ball
	_renderer.changeColor(150, 0, 0);
	SDL_Rect ball{ _appleX * (_cubeW + 1),
		_appleY * (_cubeH + 1),
		_cubeW,
		_cubeH
	};
	_renderer.renderRect(&ball);

	if (gs == Stopped)
	{
		//Menu background
		_renderer.changeColor(20, 20, 20, 20);
		SDL_Rect menu{ _windowW / 6,
			_windowH / 6,
			2* _windowW/3,
			2* _windowH/3
		};
		_renderer.renderRect(&menu);
		//loss text
		_renderer.changeColor(255, 255, 255);
		SDL_Rect loss{ _windowW / 5,
			_windowH / 4,
			3*_windowW / 5,
			1*_windowH / 6 };
		_renderer.renderTexture(_txtureLoss, &loss);
		//score text
		_txtureScore = _renderer.renderTxtToTexture( "score: " + std::to_string(body.size()), _fontFile, _fontColor, 20);
		SDL_Rect score{ _windowW / 3,
			_windowH / 2,
			_windowW / 3,
			_windowH / 9 };
		_renderer.renderTexture(_txtureScore, &score);
		//retry txt
		SDL_Rect retry{ _windowW / 4,
			8 *_windowH / 12,
			_windowW / 2,
			_windowH / 12 };
		_renderer.renderTexture(_txtureRetry1, &retry);
		retry.x = 3 * _windowW / 11;
		retry.y = 9 * _windowH / 12;
		retry.w = 10 *_windowW / 22;
		retry.h = _windowH / 12;
		_renderer.renderTexture(_txtureRetry2, &retry);
	}

	_renderer.renderScene();
}

void Game::changeApplePos(int w, int h)
{
	_appleX = (rand() % (int)(w));
	_appleY = (rand() % (int)(h));
}

void Game:: Loss()
{
	gs = Stopped;
}

void Game::Restart()
{
	_snake = new Snake(1, 1, 4);
	_appleX = _mapW / 2 + (rand() % (int)(_mapW - _mapW / 2 + 1));
	_appleY = _mapH / 2 + (rand() % (int)(_mapH - _mapH / 2 + 1));
	gs = Running;

}
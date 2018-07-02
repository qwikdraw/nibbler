#include "Game.hpp"

void	Game::pollInput(void)
{
	Input input = _graphic.Input();

	if (input.left)
	{
		_left = true;
		_right = false;
	}
	if (input.right)
	{
		_right = true;
		_left = false;
	}
	if (input.close)
		_running = false;
	if (input.one)
		_graphic.UseLib(OPENGL);
	if (input.two)
		_graphic.UseLib(NCURSES);
	if (input.three)
		_graphic.UseLib(SFML);

	_clock.Step();
	if (_clock.Total() - _lastCycleTime > _cycleTime)
	{
		_moveCycle = true;
		_lastCycleTime = _clock.Total();
	}
}

void	Game::initMap(void)
{
}

void	Game::move(void)
{
}

void	Game::render(void)
{
	_graphic.Draw(glm::ivec2(0, 0), '#');
	_graphic.Clear();
}

Game::Game(glm::ivec2 mapsize) :
_graphic(mapsize)
{
	_lastCycleTime = 0;
	_moveCycle = false;
	_left = false;
	_right = false;

	initMap();
}

Game::~Game(void)
{
}

void	Game::Run(void)
{
	pollInput();
	if (!_moveCycle)
		return;
	_moveCycle = false;
	move();
	_left = false;
	_right = false;
	render();
}

bool	Game::ShouldRun(void)
{
	return _running;
}

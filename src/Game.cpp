#include "Game.hpp"

Game::Game(glm::ivec2 mapsize) : _mapsize(mapsize)
{
	_graphic = NULL;
	_handle = NULL;
	_lib = LIB_NONE;
	loadlib(LIB_OPENGL);
	running = true;
}

Game::~Game(void)
{
	dlclose(_handle);
}

void	Game::loadlib(Libs lib)
{
	static constexpr const char* libPaths[3] = {
		"opengl/opengl.dylib",
		"ncurses/ncurses.dylib",
		"sfml/sfml.dylib"
	};

	if (_lib == lib)
		return;
	if (_handle)
		dlclose(_handle);

	_handle = dlopen(libPaths[lib], RTLD_LAZY | RTLD_LOCAL);
	if (!_handle)
	{
		std::cerr << "dlopen error: " << dlerror() << std::endl;
		exit(1);
	}

	graphic_loader_t *load = (graphic_loader_t*)dlsym(_handle, "load");
	if (!load)
	{
		std::cerr << "dlsym error: " << dlerror() << std::endl;
		exit(1);
	}
	delete _graphic;
	_graphic = load(_mapsize);
	_lib = lib;
}

void	Game::pollInput(void)
{
	_input = _graphic->Input();
	if (_input.close)
		running = false;
	if (_input.one)
		loadlib(LIB_OPENGL);
	else if (_input.two)
		loadlib(LIB_NCURSES);
	else if (_input.three)
		loadlib(LIB_SFML);
	_clock.Step();
	if (_clock.Total() - _lastCycleTime > _cycleTime)
	{
		_moveCycle = true;
		_lastCycleTime = _clock.Total();
	}
}

void	Game::render(void)
{
	_graphic->Draw(glm::ivec2(0, 0), '#');
	_graphic->Display();
}

void	Game::move(void)
{
}

void	Game::Run(void)
{
	pollInput();
	if (!_moveCycle)
		return;
	_moveCycle = false;
	move();
	render();
}

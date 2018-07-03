#include "Game.hpp"

Game::Game(glm::ivec2 mapsize) : _mapsize(mapsize), _board(mapsize.y, std::vector<char>(mapsize.x))
{
	_graphic = NULL;
	_handle = NULL;
	_lib = LIB_NONE;
	loadlib(LIB_OPENGL);
	running = true;
	_dir = Direction::LEFT;
	_cycleTime = 0.2;
	_snake.push_back(Segment{3, 0, 'O'});
	_snake.push_back(Segment{4, 0, '#'});
	_snake.push_back(Segment{5, 0, '#'});
	_moveCycle = false;
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
	if (_graphic)
		_graphic->Destroy();
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
	_graphic = load(_mapsize);
	_lib = lib;
}

void	Game::pollInput(void)
{
	Input input = _graphic->Input();
	if (input.left)
		_dir = Direction::LEFT;
	if (input.right)
		_dir = Direction::RIGHT;
	if (input.close)
		running = false;
	if (input.up)
		_dir = Direction::UP;
	if (input.down)
		_dir = Direction::DOWN;
	if (input.one)
		loadlib(LIB_OPENGL);
	else if (input.two)
		loadlib(LIB_NCURSES);
	else if (input.three)
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
	for (Segment& segment : _snake)
		_board[segment.y][segment.x] = segment.type;

	int y = 0;
	for (std::vector<char>& line : _board)
	{
		int x = 0;
		for (char& c : line)
		{
			_graphic->Draw(glm::ivec2(x, y), c);
			c = ' ';
			++x;
		}
		++y;
	}
	_graphic->Display();
}

void	Game::move(void)
{
	_snake.pop_back();
	_snake.front().type = '#';
	int x = _snake.front().x;
	int y = _snake.front().y;
	switch (_dir)
	{
		case Direction::RIGHT:
			_snake.push_front(Segment{x + 1, y, 'O'}); break;
		case Direction::LEFT:
			_snake.push_front(Segment{x - 1, y, 'O'}); break;
		case Direction::UP:
			_snake.push_front(Segment{x, y - 1, 'O'}); break;
		case Direction::DOWN:
			_snake.push_front(Segment{x, y + 1, 'O'}); break;
		default: break;
	}
}

void	Game::Run(void)
{
	render();
	pollInput();
	if (!_moveCycle)
		return;
	_moveCycle = false;
	move();
}

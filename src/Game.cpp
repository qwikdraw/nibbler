#include "Game.hpp"

Game::Game(glm::ivec2 mapsize) : _mapsize(mapsize), _board(mapsize.y, std::vector<char>(mapsize.x, ' '))
{
	_graphic = NULL;
	_handle = NULL;
	_lib = LIB_NONE;
	loadlib(LIB_OPENGL);
	running = true;
	_snakeDir = Direction::LEFT;
	_cycleTime = 0.2;
//	int x;
//	int y;
	_snake.push_back(Segment{7, 5, 'O'});
	_snake.push_back(Segment{8, 5, '#'});
	_snake.push_back(Segment{9, 5, '#'});
	_moveCycle = false;
	_board[7][7] = '@';
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
	if (input.left && (_snakeDir == Direction::UP || _snakeDir == Direction::DOWN))
		_dir = Direction::LEFT;
	if (input.right && (_snakeDir == Direction::UP || _snakeDir == Direction::DOWN))
		_dir = Direction::RIGHT;
	if (input.up && (_snakeDir == Direction::LEFT || _snakeDir == Direction::RIGHT))
		_dir = Direction::UP;
	if (input.down && (_snakeDir == Direction::LEFT || _snakeDir == Direction::RIGHT))
		_dir = Direction::DOWN;
	if (input.close)
	{
		running = false;
		_moveCycle = false;
	}
	if (input.one)
		loadlib(LIB_OPENGL);
	else if (input.two)
		loadlib(LIB_NCURSES);
	else if (input.three)
		loadlib(LIB_SFML);
	clock.Step();
	if (clock.Total() - _lastCycleTime > _cycleTime)
	{
		_moveCycle = true;
		_lastCycleTime = clock.Total();
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
			_graphic->Draw(glm::ivec2(x++, y), c);
		++y;
	}
	_graphic->Display();
}

void	Game::move(void)
{
	if (_dir == Direction::LEFT && _snakeDir != Direction::RIGHT)
		_snakeDir = _dir;
	if (_dir == Direction::RIGHT && _snakeDir != Direction::LEFT)
		_snakeDir = _dir;
	if (_dir == Direction::UP && _snakeDir != Direction::DOWN)
		_snakeDir = _dir;
	if (_dir == Direction::DOWN && _snakeDir != Direction::UP)
		_snakeDir = _dir;
	_board[_snake.back().y][_snake.back().x] = ' ';
	_snake.pop_back();
	_snake.front().type = '#';
	int x = _snake.front().x;
	int y = _snake.front().y;
	Segment new_head;
	switch (_snakeDir)
	{
		case Direction::RIGHT:
			new_head = Segment{x + 1, y, 'O'}; break;
		case Direction::LEFT:
			new_head = Segment{x - 1, y, 'O'}; break;
		case Direction::UP:
			new_head = Segment{x, y - 1, 'O'}; break;
		case Direction::DOWN:
			new_head = Segment{x, y + 1, 'O'}; break;
		default: break;
	}
	if (new_head.x < 0 || new_head.y < 0 || new_head.x >= _mapsize.x || new_head.y >= _mapsize.y
	|| _board[new_head.y][new_head.x] == '#')
	{
		running = false;
	}
	else
		_snake.push_front(new_head);
}

void	Game::Run(void)
{
	render();
	pollInput();
	if (_moveCycle)
	{
		_cycleTime = pow(_cycleTime, 1 + pow(_cycleTime, 4));
		_moveCycle = false;
		move();
	}
	if (!running && _graphic)
		_graphic->Destroy();
}

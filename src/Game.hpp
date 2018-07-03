#pragma once

#include <dlfcn.h>
#include <iostream>
#include <vector>
#include <list>
#include "IGraphic.hpp"
#include "Time.hpp"

typedef	IGraphic* graphic_loader_t(glm::ivec2);

enum Libs
{
	LIB_NONE = -1,
	LIB_OPENGL,
	LIB_NCURSES,
	LIB_SFML
};

struct	Segment
{
	int		x;
	int		y;
	char	type;
};

enum class Direction{UP, RIGHT, DOWN, LEFT};

class	Game
{
	glm::ivec2 _mapsize;
	double _lastCycleTime;
	double _cycleTime;
	bool _moveCycle;
	IGraphic* _graphic;
	Libs _lib;
	void* _handle;
	Direction _dir;
	Direction _snakeDir;
	std::list<Segment> _snake;
	std::vector<std::vector<char>> _board;

	void	loadlib(Libs);
	void	pollInput(void);
	void	move(void);
	void	render(void);
public:
	Time clock;
	bool running;
	Game(glm::ivec2 mapsize);
	~Game(void);
	void	Run(void);
};

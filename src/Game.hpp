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
	Libs _lib;
	void* _handle;
	IGraphic* _graphic;
	std::vector<std::vector<char>> _board;
	Time _clock;

	// Snake
	Direction _dir;
	std::list<Segment> _snake;
	Direction _snakeDir;
	int _snakeGrow;

	void	loadlib(Libs);
	void	pollInput(void);
	void	move(void);
	void	render(void);
	void	spawnFood(void);
public:
	bool running;
	Game(glm::ivec2 mapsize);
	~Game(void);
	void	Run(void);
	int score;
};

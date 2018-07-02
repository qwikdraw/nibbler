#pragma once

#include <dlfcn.h>
#include <iostream>
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

class	Game
{
	glm::ivec2 _mapsize;
	Time _clock;
	double _lastCycleTime;
	static constexpr double _cycleTime = 0.5;
	bool _moveCycle;
	IGraphic* _graphic;
	Libs _lib;
	void* _handle;
	Input _input;

	void	loadlib(Libs);
	void	pollInput(void);
	void	move(void);
	void	render(void);
public:
	bool running;
	Game(glm::ivec2 mapsize);
	~Game(void);
	void	Run(void);
};

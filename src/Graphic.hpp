#pragma once

#include "IGraphic.hpp"
#include <dlfcn.h>
#include <iostream>

typedef	IGraphic* cInterface_t(glm::ivec2);

enum Libs
{
	OPENGL = 0,
	NCURSES = 1,
	SFML = 2
};

class	Graphic
{

	IGraphic *_graphic;
	Libs _lib;
	void *_handle;
	glm::ivec2 _mapsize;
	
public:

	Graphic(glm::ivec2 mapsize);
	~Graphic(void);

	void	UseLib(Libs);

	//! forwarding functions to IGraphic
	void	Draw(const glm::ivec2&, char);
	void	Clear(void);
	Input	Input(void);
};

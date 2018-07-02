#pragma once

#include "IGraphic.hpp"
#include <dlfcn.h>
#include <iostream>

typedef	IGraphic* cInterface_t(glm::ivec2);

enum Libs
{
	OPENGL = 0,
	NCURSES = 1,
	SFM = 2
};

IGraphic *GraphicLoader(Libs type, const glm::ivec2& size);

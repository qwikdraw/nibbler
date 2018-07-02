#pragma once

#include "CoreInclude.hpp"
#include "Window.hpp"
#include "Image2D.hpp"
#include "../../src/IGraphic.hpp"

extern "C"
{
	IGraphic* load_opengl(glm::ivec2 mapsize);
}

class	GLRender : public IGraphic
{

	Window _window;
	Image2D _image;
	std::vector<unsigned char> _data;
	size_t _width;
	size_t _height;
	uint32_t _colors[255];
	
public:

	GLRender(glm::ivec2 mapsize);
	~GLRender(void);
	
	void	Draw(glm::ivec2 pos, char c);
	void	Clear(void);
	struct Input	Input(void);
};

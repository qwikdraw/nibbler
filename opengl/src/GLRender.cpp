#include "GLRender.hpp"

GLRender::GLRender(glm::ivec2 mapsize) : _window(800, 800, "GLRender")
{
	glClearColor(0.4, 0.45, 0.7, 1);
	_data.resize(mapsize.x * mapsize.y * 4);
	_width = mapsize.x;
	_height = mapsize.y;

	// assigning each character a 'random' color
	for (size_t i = 0; i < 255; i++)
	{
		_colors[i] = (i * 1772) % 255 +
			256 * ((i * 97) % 255) +
			256 * 256 * ((i * 589) % 255) +
			(size_t)256 * 256 * 256 * 255;
	}
}

GLRender::~GLRender(void)
{
	_window.Close();
}

void	GLRender::Render(glm::ivec2 pos, char c)
{
	size_t i = (pos.x + pos.y * _width) * 4;

	std::memmove(&_data[i], &_colors[(unsigned char)c], 4);
}

void	GLRender::Clear(void)
{
	_window.Clear();
	_image.Render(_data, _width, _height);
	_window.Render();
	std::memset(&_data[0], 0, _width * _height * 4);
}

Input	GLRender::Input(void)
{
	struct Input out = {false, false, false, false, false, false};
	
	if (_window.Key(GLFW_KEY_LEFT))
		out.left = true;
	if (_window.Key(GLFW_KEY_RIGHT))
		out.right = true;
	if (_window.ShouldClose() || _window.Key(GLFW_KEY_ESCAPE))
		out.close = true;
	if (_window.Key('1'))
		out.key1 = true;
	if (_window.Key('2'))
		out.key2 = true;
	if (_window.Key('3'))
		out.key3 = true;

	return out;
}

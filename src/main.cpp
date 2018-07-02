#include "IGraphic.hpp"
#include <iostream>
#include <dlfcn.h>

typedef IGraphic* c_interface_t(glm::ivec2);

static IGraphic	*GraphicFactory(const std::string& path,
				const std::string& cInterface,
				const glm::ivec2 size)
{
	void *handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!handle)
	{
		std::cerr << "invalid library" << std::endl;
		exit(1);
	}
	
	c_interface_t *i = (c_interface_t*)dlsym(handle, cInterface.c_str());
	if (!i)
	{
		std::cerr << "invalid symbols" << std::endl;
		exit(1);
	}
	return i(size);
}

int	main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cerr
			<< "usage: ./nibbler <width> <height>\n"
			<< "where\n"
			<< "  <width>  ∈ [low, high]\n"
			<< "  <height> ∈ [low, high]" << std::endl;
		exit(1);
	}
	glm::ivec2 mapsize = {std::atoi(argv[1]), std::atoi(argv[2])};


	IGraphic *graphic = GraphicFactory("opengl/opengl.dylib", "load_opengl", mapsize);

	while (1)
	{
		graphic->Draw(glm::ivec2(5, 5), '0');
		graphic->Clear();
		Input input = graphic->Input();
		if (input.close)
			break;
	}
	
	return 0;
}

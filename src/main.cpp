#include "IGraphic.hpp"
#include <iostream>

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
	(void)argv;

	void *handle = dlopen(opengl/opengl.dylib, RTLD_LAZY | RTLD_LOCAL);
	if (handle == NULL)
	{
		std::cout << "Bad thing" << std::endl;
		exit(1);
	}
	IGraphic *graphic = reinterpret_cast<std::function<IGraphic*(glm::ivec2)>>dlsym(handle, "load_opengl");

	if (graphic == NULL)
	{
		std::cout << "other Bad THING~!!!" << std::endl;
		exit(1);
	}	
	return 0;
}

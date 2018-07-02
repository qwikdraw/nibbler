#include "IGraphic.hpp"
#include <iostream>

int	main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cerr << "usage: ./nibbler <width> <height>\n where\n  width ∈ [low, high]\n  height ∈ [low, high]" << std::endl;
		exit(1);
	}
	(void)argv;
	return 0;
}

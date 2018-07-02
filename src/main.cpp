#include <iostream>
#include "Game.hpp"

int	main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cerr
			<< "usage: ./nibbler <width> <height>\n"
			<< "where\n"
			<< "  <width>  ∈ [10, 50]\n"
			<< "  <height> ∈ [10, 50]" << std::endl;
		exit(1);
	}
	glm::ivec2 mapsize = {std::atoi(argv[1]), std::atoi(argv[2])};
	if (mapsize.x < 10 || mapsize.y < 10 || mapsize.x > 50 || mapsize.y > 50)
	{
		std::cerr << "invalid map size" << std::endl;
		exit(1);
	}

	Game game(mapsize);
	
	while (game.ShouldRun())
		game.Run();
	
	return 0;
}

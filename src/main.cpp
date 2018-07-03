#include <iostream>
#include "Game.hpp"

static void error_usage(void)
{
	std::cerr
		<< "usage: ./nibbler <width> <height>\n"
		<< "where\n"
		<< "  <width>  ∈ [10, 50]\n"
		<< "  <height> ∈ [10, 50]" << std::endl;
	exit(1);
}

int	main(int argc, char** argv)
{
	if (argc != 3)
		error_usage();
	glm::ivec2 mapsize = {std::atoi(argv[1]), std::atoi(argv[2])};
	if (mapsize.x < 10 || mapsize.y < 10 || mapsize.x > 50 || mapsize.y > 50)
	{
		std::cerr << "nibbler: invalid map dimensions: "
			<< argv[1] << ", " << argv[2] << std::endl;
		error_usage();
	}

	Game game(mapsize);
	
	while (game.running)
		game.Run();
	std::cout
		<< "Game Over\n"
		<< "Your score: " << game.clock.Total() << std::endl;
	return 0;
}

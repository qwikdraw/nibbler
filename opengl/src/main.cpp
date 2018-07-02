
#include "GLRender.hpp"

int	main(void)
{
	GLRender window(glm::ivec2(10, 10));
	
	while (1)
	{
		window.Draw(glm::ivec2(5, 5), 'o');
		window.Clear();
		Input input = window.Input();
		if (input.close)
			break;
	}
}

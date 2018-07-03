#pragma once

#include "../../src/IGraphic.hpp"
#include <SFML/Graphics.hpp>

class	Sfml : public IGraphic
{
public:

	Sfml(glm::ivec2 mapsize);

	void	Draw(glm::ivec2 pos, char c);
	void	Display(void);
	struct Input	Input(void);
	void	Destroy(void);
};

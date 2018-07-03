#include "Sfml.hpp"

extern "C" IGraphic	*load(glm::ivec2 mapsize)
{
	return new Sfml(mapsize);
}

Sfml::Sfml(glm::ivec2 mapsize)
{
	(void)mapsize;
}

void	Sfml::Draw(glm::ivec2 pos, char c)
{
	(void)pos;
	(void)c;
}

void	Sfml::Display(void)
{
}

struct Input	Sfml::Input(void)
{
	struct Input out = {false, false, false, false, false, false, false, false};
	return out;
}

void	Sfml::Destroy(void)
{
}

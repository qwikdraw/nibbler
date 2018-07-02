#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

struct Input
{
	bool	left;
	bool	right;
	bool	close;
	bool	one;
	bool	two;
	bool	three;
};

class IGraphic
{
public:
	IGraphic(glm::ivec2 grid_size);
	virtual ~IGraphic(void) = 0;
	virtual void Draw(glm::ivec2, char) = 0;
	virtual void Clear(void) = 0;
	virtual Input Input(void) = 0;
};

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
protected:
	IGraphic(void) {}
	
public:
	virtual ~IGraphic(void) {};
	virtual void Draw(glm::ivec2, char) = 0;
	virtual void Display(void) = 0;
	virtual Input Input(void) = 0;
};

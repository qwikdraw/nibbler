#pragma once

#define SCREENIMAGE_VERTEX_SHADER_PATH "screenImageVertex.glsl"
#define SCREENIMAGE_FRAGMENT_SHADER_PATH "screenImageFrag.glsl"

#include "CoreInclude.hpp"
#include "ShadingProgram.hpp"

//! always give this class RGBA values
class	Image2D
{
	static const std::vector<float> _vertexArray;
	static const std::vector<float> _uvArray;

	ShadingProgram *_program;
	GLuint _vertexArrayID;
	GLuint _uvArrayID;
	GLuint _textureID;
	GLuint _textureLocationID;
	
public:

	//! does not bind a texture
	Image2D(void);
	~Image2D(void);

	//! renders and binds a texture
	void	Render(std::vector<unsigned char> data, size_t width, size_t height);
	
	//! renders with the previously bound texture
	void	Render(void);
};

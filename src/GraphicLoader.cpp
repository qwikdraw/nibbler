#include "GraphicLoader.hpp"

IGraphic *GraphicLoader(Libs type, const glm::ivec2& size)
{
	static constexpr char const *cInterfaces[3] = {"load_opengl",
						       "load_ncurses",
						       "load_sfml"};
	static constexpr char const *libPaths[3] = {"opengl/opengl.dylib",
						    "ncurses/ncurses.dylib",
						    "sfml/sfml.dylib"};
	
	void *handle = dlopen(libPaths[type], RTLD_LAZY | RTLD_LOCAL);
	if (!handle)
	{
		std::cerr << "invalid library" << std::endl;
		exit(1);
	}

	cInterface_t *i = (cInterface_t*)dlsym(handle, cInterfaces[type]);
	if (!i)
	{
		std::cerr << "invalid symbols" << std::endl;
		exit(1);
	}
	return i(size);
}

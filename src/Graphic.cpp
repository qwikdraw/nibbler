#include "Graphic.hpp"

Graphic::Graphic(glm::ivec2 mapsize) :
_mapsize(mapsize)
{
	_handle = NULL;
	_lib = NCURSES; // as long as it isnt same as argument for UseLib
	UseLib(OPENGL);
}

Graphic::~Graphic(void)
{
	dlclose(_handle);
}

void	Graphic::UseLib(Libs lib)
{
	static constexpr char const *cInterfaces[3] = {"load_opengl",
						       "load_ncurses",
						       "load_sfml"};
	static constexpr char const *libPaths[3] = {"opengl/opengl.dylib",
						    "ncurses/ncurses.dylib",
						    "sfml/sfml.dylib"};

	if (_lib == lib)
		return;
	if (_handle)
		dlclose(_handle);
	
	_handle = dlopen(libPaths[lib], RTLD_LAZY | RTLD_LOCAL);
	if (!_handle)
	{
		std::cerr << "dlopen error: " << dlerror() << std::endl;
		exit(1);
	}

	cInterface_t *i = (cInterface_t*)dlsym(_handle, cInterfaces[lib]);
	if (!i)
	{
		std::cerr << "dlsym error: " << dlerror() << std::endl;
		exit(1);
	}
	_graphic = i(_mapsize);
	_lib = lib;
}

void	Graphic::Draw(const glm::ivec2& pos, char c)
{
	_graphic->Draw(pos, c);
}

void	Graphic::Clear(void)
{
	_graphic->Clear();
}

Input	Graphic::Input(void)
{
	return _graphic->Input();
}

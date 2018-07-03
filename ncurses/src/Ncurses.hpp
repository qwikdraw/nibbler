#include "../../src/IGraphic.hpp"
#include <ncurses.h>

class	Ncurses : public IGraphic
{
public:

	Ncurses(glm::ivec2 mapsize);

	void	Draw(glm::ivec2 pos, char c);
	void	Display(void);
	struct Input	Input(void);
	void	Destroy(void);
};

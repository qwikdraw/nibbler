#include "Ncurses.hpp"

extern "C" IGraphic	*load(glm::ivec2 mapsize)
{
	return new Ncurses(mapsize);
}

Ncurses::Ncurses(glm::ivec2 mapsize)
{
	(void)mapsize;
	initscr();
	timeout(0);
	curs_set(0);
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	start_color();			      
}

void	Ncurses::Draw(glm::ivec2 pos, char c)
{
	mvprintw(pos.x, pos.y, "%c", c);
}

void	Ncurses::Display(void)
{
	refresh();
}

struct Input	Ncurses::Input(void)
{
	struct Input out = {false, false, false, false, false, false, false, false};
	char c = getch();
	if (c == '1')
		out.one = true;
	else if (c == '2')
		out.two = true;
	else if (c == '3')
		out.three = true;

	if (c == '\033')
	{
		if (!getch())
		{
			out.close = true;
			return out;
		}
		c = getch();
		if (c == 'D')
			out.left = true;
		else if (c == 'C')
			out.right = true;
		else if (c == 'B')
			out.down = true;
		else if (c == 'A')
			out.up = true;
	}
	return out;
}

void	Ncurses::Destroy(void)
{
	endwin();
	delete this;
}

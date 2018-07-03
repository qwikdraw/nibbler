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
	mvaddch(pos.y, pos.x, c);
}

void	Ncurses::Display(void)
{
	refresh();
}

struct Input	Ncurses::Input(void)
{
	struct Input out = {false, false, false, false, false, false, false, false};
	int c = getch();
	if (c == '1')
		out.one = true;
	else if (c == '2')
		out.two = true;
	else if (c == '3')
		out.three = true;
	else if (c == 27)
		out.close = true;
	else if (c == KEY_LEFT)
		out.left = true;
	else if (c == KEY_RIGHT)
		out.right = true;
	else if (c == KEY_DOWN)
		out.down = true;
	else if (c == KEY_UP)
		out.up = true;
	return out;
}

void	Ncurses::Destroy(void)
{
	endwin();
	delete this;
}

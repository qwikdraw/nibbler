#include "Ncurses.hpp"

extern "C" IGraphic	*load(glm::ivec2 mapsize)
{
	return new Ncurses(mapsize);
}

static void	draw_square(int y, int x)
{
	mvaddch(y, x * 2, ' ');
	mvaddch(y, x * 2 + 1, ' ');
}

Ncurses::Ncurses(glm::ivec2 mapsize)
{
	initscr();
	timeout(0);
	curs_set(0);
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	start_color();

	init_color(COLOR_RED, 1000, 100, 500); // head color
	init_color(COLOR_GREEN, 1000, 700, 7000); // body color
	init_color(COLOR_BLUE, 1000, 100, 100); // food color
	init_color(COLOR_YELLOW, 300, 1000, 1000); // wall color

	init_pair(0, COLOR_WHITE, COLOR_BLACK); // default
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_WHITE, COLOR_BLUE);
	init_pair(4, COLOR_WHITE, COLOR_YELLOW);
	
	attron(COLOR_PAIR(4));
	for (int i = 0; i < mapsize.x + 2; i++)
	{
		draw_square(mapsize.y + 1, i);
		draw_square(0, i);
	}
	for (int i = 0; i < mapsize.y + 2; i++)
	{
		draw_square(i, mapsize.x + 1);
		draw_square(i, 0);
	}
	attroff(COLOR_PAIR(4));
}

void	Ncurses::Draw(glm::ivec2 pos, char c)
{
	int palete = 0;
	
	if (c == 'O')
		palete = 1;
	else if (c == '#')
		palete = 2;
	else if (c == '@')
		palete = 3;
	else if (c == 'x')
		palete = 4;

	attron(COLOR_PAIR(palete));
	draw_square(pos.y + 1, pos.x + 1);
	attroff(COLOR_PAIR(palete));
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

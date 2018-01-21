#include "ncurses.h"
#include <string.h>

int main()
{
	initscr();
	if (has_colors())
	{
		use_default_colors();
		start_color();
		init_pair(1, COLOR_RED, -1);
	}
	
	printw("Line 1\n");
	attrset(COLOR_PAIR(1));
	printw("Line 2\n");
	getch();
	endwin();
	return 0;
}


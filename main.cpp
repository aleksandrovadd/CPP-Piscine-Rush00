#include "ncurses.h"
#include "GameCycle.hpp"

void    exitGame(int score)
{
	timeout(-1);
	clear();
	refresh();
	printw("Thank you. Good job! Your SCORE is: %d", score);
	getch();
	endwin();
}

int main()
{
    initscr();
    GameCycle cycle;
    int score = cycle.startCycle();

	exitGame(score);
	return 0;
}
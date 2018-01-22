#include <iostream>
#include "ncurses.h"
#include "GameCycle.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

void	GameCycle::initBackground()
{
	for (int i = 0; i < MAX_STARS_COUNT; i++)
	{
		st[i].x = rand()%screenWidth;
		st[i].y = rand()%screenHeight;
		st[i].c = '.';
	}
}

void	GameCycle::moveBackground()
{
	for (int i = 0; i < MAX_STARS_COUNT; ++i)
	{
		st[i].x--;
		if (st[i].x < 0)
		{
			st[i].x = screenWidth + 1;
			st[i].y = rand()%screenHeight;
		}
	}
}
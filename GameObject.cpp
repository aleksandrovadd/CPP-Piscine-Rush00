//
// Created by maks on 19.01.18.
//

#include "GameObject.hpp"

void	GameObject::hit(int damage)
{
	hp -= damage;
}

void	GameObject::chooseColor(void)
{
	if (has_colors())
	{
		use_default_colors();
		start_color();
		if (PLAYER)
			init_pair(1, COLOR_BLUE, -1);
		if (ENEMY)
			init_pair(2, COLOR_RED, -1);
	}
}
//
// Created by maks on 19.01.18.
//

#include "Enemy.hpp"

Enemy::Enemy()
{
	chooseColor();
	hp = 10;
	type = 2;
	actionDelimiter = 3;
	shape.height = 3;
	shape.str = new std::string[3];
	shape.str[0] = "# #";
	shape.str[1] = " ##";
	shape.str[2] = "# #";
	shape.max_width = 3;
	shape.posX = 3;
	shape.posY = 10;
	
}

Action Enemy::action(int tick)
{
	Action act;

	if (!(tick % 30))
		if (shape.posX > 2)
			shape.posX--;
	act.senderType = ENEMY;
	act.action = END_ACTION;

	return (act);
}
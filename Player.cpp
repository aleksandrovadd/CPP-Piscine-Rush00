//
// Created by maks on 19.01.18.
//

#include "Player.hpp"

Player::Player()
{
	chooseColor();
	hp = 100;
	type = 1;
	actionDelimiter = 1;
	shape.height = 3;
	shape.str = new std::string[3];
	shape.str[0] = "#  ";
	shape.str[1] = " ##";
	shape.str[2] = "#  ";
	shape.max_width = 3;
	shape.posX = 10;
	shape.posY = 10;
}

Action Player::action(int tick)
{
	Action act;

	act.action = END_ACTION;
	act.senderType = PLAYER;

	if (hp <= 0)
	{
		act.action = DEATH;
		return act;
	}
	int ch = getch();
	switch (ch)
	{
		case ERR:
			break;
		case KEY_F(2):
            act.action = DEATH;
            return act;
			break;
		case KEY_UP:
			shape.posY--;
			break;
		case KEY_DOWN:
			shape.posY++;
			break;
		case KEY_ENTER:
			shape.posY = 1;
			shape.posX = 1;
			break;
		case KEY_LEFT:
			shape.posX--;
			break;
		case KEY_RIGHT:
			shape.posX++;
			break;
		default:
			break;
	}
    return act;
}
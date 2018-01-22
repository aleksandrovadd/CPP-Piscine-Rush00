//
// Created by maks on 19.01.18.
//

#include "Player.hpp"

Player::Player()
{
	hp = 100;
	type = 1;
	actionDelimiter = 1;
	shootSpeed = 2000;
	shape.height = 3;
	shape.str = new std::string[3];
	shape.str[0] = "#  ";
	shape.str[1] = " ##";
	shape.str[2] = "#  ";
	shape.max_width = 3;
	shape.posX = 10;
	shape.posY = 10;
}

Player::~Player()
{
    delete [] shape.str;
}

Action Player::action(int tick)
{
	static Action act;


	act.senderType = PLAYER;
	if (hp <= 0)
	{
		act.action = DEATH;
		return act;
	}
	if (act.action != SHOOT && !(tick % shootSpeed))
	{
		act.action = SHOOT;
		return act;
	}
	act.action = END_ACTION;
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
			if (shape.posY >= 0)
				shape.posY--;
			break;
		case KEY_DOWN:
			if (shape.posY <= screenHeight - shape.height)
				shape.posY++;
			break;
		case KEY_ENTER:
			hp += 1000;
			break;
		case KEY_LEFT:
			if (shape.posX > 0)
				shape.posX--;
			break;
		case KEY_RIGHT:
			if (shape.posX < screenWidth - shape.max_width)
				shape.posX++;
			break;
		default:
			break;
	}
    return act;
}
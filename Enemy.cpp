//
// Created by maks on 19.01.18.
//

#include "Enemy.hpp"

Enemy::Enemy()
{
	hp = 10;
	type = ENEMY;
	actionDelimiter = 100;
	shape.height = 3;
    shootSpeed = 8000;
	shape.str = new std::string[3];
	shape.str[0] = "###";
	shape.str[1] = " # ";
	shape.str[2] = "###";
	shape.max_width = 3;
	shape.posX = 10;
	shape.posY = 10;
}

Enemy::~Enemy()
{
    delete [] shape.str;
}

Action Enemy::action(int tick)
{
	Action act;

	act.senderType = type;
	act.action = END_ACTION;
    if (hp <= 0)
    {
        act.action = DEATH;
        return act;
    }
	if (!(tick % actionDelimiter))
	{
        if (!(tick % shootSpeed))
        {
            act.action = SHOOT;
            return act;
        }
        if (shape.posX > -20)
			shape.posX--;
        if (shape.posX == -shape.max_width)
			act.action = DEATH;
	}
	return (act);
}

Enemy::Enemy(Enemy const &rhs)
{
    *this = rhs;
}

Enemy &Enemy::operator=(Enemy const &src)
{
    this->type = src.type;
    this->hp = src.hp;
    this->shape = src.shape;
    this->shootSpeed = src.shootSpeed;
    this->actionDelimiter = src.actionDelimiter;
    return *this;
}
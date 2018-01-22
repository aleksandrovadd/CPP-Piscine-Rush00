//
// Created by maks on 19.01.18.
//

#include "Bullet.hpp"

Bullet::Bullet()
{
    hp = 20;
    type = PLAYER_BULLET;
    actionDelimiter = 75;
    shape.height = 1;
    shape.str = new std::string[1];
    shape.str[0] = "*";
    shape.max_width = 1;
    shape.posX = 0;
    shape.posY = 0;
}

Bullet::Bullet(Bullet const &rhs)
{
    *this = rhs;
}

Bullet::~Bullet()
{
    delete [] shape.str;
}

Action Bullet::action(int tick)
{
    Action act;
    act.senderType = type;
    act.action = END_ACTION;
    if (!(tick % actionDelimiter))
    {
        if (type == PLAYER_BULLET)
            shape.posX++;
        if (type == ENEMY_BULLET)
            shape.posX--;
        if (shape.posX < -1 || shape.posX > 500)
            act.action = DEATH;
    }
    return (act);
}


Bullet &Bullet::operator=(Bullet const &src)
{
    this->type = src.type;
    this->hp = src.hp;
    this->shape = src.shape;
    this->shootSpeed = src.shootSpeed;
    this->actionDelimiter = src.actionDelimiter;
    return *this;
}
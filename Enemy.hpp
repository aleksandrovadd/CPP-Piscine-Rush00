//
// Created by maks on 19.01.18.
//

#ifndef UNTITLED_ENEMY_HPP
#define UNTITLED_ENEMY_HPP

#include "GameObject.hpp"

class Enemy : public GameObject
{
public:
	Enemy();
	Action action(int tick);
};


#endif //UNTITLED_ENEMY_HPP

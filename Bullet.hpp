//
// Created by maks on 19.01.18.
//

#ifndef UNTITLED_BULLET_HPP
#define UNTITLED_BULLET_HPP

#include "GameObject.hpp"

class Bullet : public GameObject
{
public:
	Action action(int tick);
};


#endif //UNTITLED_BULLET_HPP

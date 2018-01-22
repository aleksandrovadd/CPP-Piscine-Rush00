//
// Created by maks on 19.01.18.
//

#ifndef UNTITLED_BULLET_HPP
#define UNTITLED_BULLET_HPP

#include "GameObject.hpp"

class Bullet : public GameObject
{
public:
	Bullet();
    Bullet(Bullet const &rhs);
    ~Bullet();
	Action	action(int tick);

    Bullet &operator=(Bullet const &src);
};


#endif //UNTITLED_BULLET_HPP

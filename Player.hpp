//
// Created by maks on 19.01.18.
//

#ifndef UNTITLED_PLAYER_HPP
#define UNTITLED_PLAYER_HPP

#include "GameObject.hpp"

class Player : public GameObject
{
public:
	Player();
    ~Player();
	Action  action(int tick);
    int     screenWidth;
    int     screenHeight;
};


#endif //UNTITLED_PLAYER_HPP

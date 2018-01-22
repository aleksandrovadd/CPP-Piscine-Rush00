//
// Created by maks on 19.01.18.
//

#ifndef UNTITLED_GAMEOBJECT_HPP
#define UNTITLED_GAMEOBJECT_HPP

#include <iostream>
#include "ncurses.h"

#define PLAYER 1
#define PLAYER_BULLET 2
#define ENEMY 3
#define ENEMY_BULLET 4

#define END_ACTION 0
#define SHOOT 1
#define DEATH 2
#define DAMAGE 3

typedef struct 		s_back
{
    int				x;
    int				y;
    char			c;
}					t_back;

typedef struct      s_shape
{
	std::string*    str;
	int             height;
	int             max_width;
	int             posX;
	int             posY;
}                   t_shape;

typedef struct		s_action
{
	int 			action;
	int 			senderType;
	int 			senderIndex;
    int             targetType;
    int             targetIndex;
}					Action;

class GameObject
{
public:
	int     			type;
	int     			hp;
	t_shape 			shape;
	int 				shootSpeed;
	virtual Action      action(int tick) = 0;
	void                hit(int damage);

    GameObject();
    GameObject(GameObject const &rhs);
    virtual ~GameObject();

    GameObject &operator=(GameObject const &src);

protected:
	int     			actionDelimiter;


};


#endif //UNTITLED_GAMEOBJECT_HPP

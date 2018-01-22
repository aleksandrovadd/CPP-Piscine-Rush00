//
// Created by Maksym Paziuk on 20.01.18.
//

#ifndef FT_RETRO_GAMECYCLE_HPP
#define FT_RETRO_GAMECYCLE_HPP

#include <ctime>
#include "ncurses.h"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

// Init scene and entities
// Act by every entity
// Draw -> repeat until player is killed

#define MAX_ENEMIES_COUNT 50
#define MAX_BULLETS_COUNT 512
#define MAX_STARS_COUNT 50

class GameCycle
{
public:
    GameCycle();
    GameCycle(GameCycle const &rhs);
    ~GameCycle();
    int    startCycle();

    GameCycle &operator=(GameCycle const &src);

protected:
    Player      player;
    Enemy**     enemies;
    int         enemiesCount;
    int         enemiesMax;
    Bullet**    bullets;
    int         bulletsCount;
    int         score;
    long int    tick;
    bool        exitFlag;
    t_back      st[MAX_STARS_COUNT];

    int         screenWidth;
    int         screenHeight;

    void        initEnemys();
    void        initScreen();
    void        initBullets();
    void        initBackground();
    void        moveBackground();

    void        addEnemy();
    void        removeEnemy(int index);

    void        addBullet(int type, int x, int y);
    void        removeBullet(int index);

    void        actEnemies();
    void        actPlayer();
    void        actBullet();

    void        draw();
    void        makeAction(Action action); //Callback function to create bullets, etc.

private:
    int         collide(GameObject  *obj1, GameObject *obj2);
    void        output(GameObject *obj);
};


#endif //FT_RETRO_GAMECYCLE_HPP

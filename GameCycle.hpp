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

class GameCycle
{
public:
    GameCycle();
    ~GameCycle();
    int    startCycle();

protected:
    Player      player;
    Enemy**     enemies;
    int         enemiesCount;
    int         enemiesMax;
    Bullet      bullets[256];
    int         bulletsCount;
    int         score;
    long int    tick;
    bool        exitFlag;

    int         screenWidth;
    int         screenHeight;
    int         offset;

    void        initEnemys();
    void        initBullets();
    void        initPlayer();
    void        initScreen();

    void        addEnemy();
    void        addBullet(int type, int x, int y, int dirX, int dirY);
    void        removeBullet(int index);
    void        removeEnemy(Enemy *enemy, int index);

    void        actBullets();
    void        actEnemies();
    void        actPlayer();
    void        draw();
    void        makeAction(Action action); //Callback function to create bullets, etc.

private:
    int         collide(GameObject  *obj1, GameObject *obj2);
    void        output(GameObject *obj);
};


#endif //FT_RETRO_GAMECYCLE_HPP

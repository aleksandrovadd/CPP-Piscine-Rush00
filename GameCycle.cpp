//
// Created by Maksym Paziuk on 20.01.18.
//

#include "GameCycle.hpp"

GameCycle::GameCycle()
{
    score = 0;
    tick = 0;
    exitFlag = false;
    offset = 10;
    enemiesMax = 1;

    std::srand(std::time(0));
    initScreen();
    initEnemys();
    initBullets();
    initPlayer();
    startCycle();
}

GameCycle::~GameCycle()
{
    for (int i = 0; i < MAX_ENEMIES_COUNT; i++)
    {
        if (enemies[i])
            delete enemies[i];
    }
    delete[] enemies;
}

void    GameCycle::initEnemys()
{
    enemiesCount = 0;
    enemies = new Enemy*[MAX_ENEMIES_COUNT];
    for (int i = 0; i < MAX_ENEMIES_COUNT; i++)
    {
        enemies[i] = nullptr;
    }
    addEnemy();
    // todo: implement enemies and add correct init
}

void    GameCycle::initBullets()
{
    bulletsCount = 0;
    // todo: implement bullets and add correct init
}

void    GameCycle::initPlayer() // Just in case, to gain more control over Player
{
    player.hp = 100;
    // todo: remove this func if it will not be needed
}

void    GameCycle::initScreen()
{
    noecho();
    getmaxyx(stdscr, screenHeight, screenWidth);
    curs_set(false);
    timeout(0);
    cbreak();
    keypad(stdscr, true);
}

// Check collisions with all enemies
// Check collision with all bullets
// Do action!
// Repeat until there is nothing to do
// Respond with apropriate actions

void    GameCycle::actPlayer()
{
    Action  action;

    do
    {
        for (int i = 0; i < enemiesCount; i++) // Collide player with all enemies
            if (collide((GameObject*)&player, (GameObject*)enemies[i]))
            {
                action.action = DEATH;
                action.senderType = PLAYER;
                makeAction(action);
                break;
            }
        for (int i = 0; i < bulletsCount; i++) // Collide player with all enemy bullets
            if (bullets[i].type == ENEMY_BULLET &&
                    collide((GameObject*)&player, (GameObject*)&bullets[i]))
            {
                action.action = DAMAGE;
                action.senderType = PLAYER;
                action.targetType = ENEMY_BULLET;
                action.targetIndex = i;
                makeAction(action);
                action.action = DEATH;
                action.senderType = ENEMY_BULLET;
                makeAction(action);
                continue;
            }
        action = player.action(tick);
        makeAction(action);
    }
    while (action.action != END_ACTION);

}

void    GameCycle::actBullets()
{
    Action  action;

    for (int i = 0; i < bulletsCount && bulletsCount; i++)
    {
        do
        {
            for (int j = 0; j < enemiesCount; j++) // Collide player bullet with all enemies
                if (bullets[i].type == PLAYER_BULLET &&
                        collide((GameObject*)&bullets[i], (GameObject*)enemies[j]))
                {
                    action.action = DAMAGE;
                    action.senderType = ENEMY;
                    action.senderIndex = j;
                    action.targetType = PLAYER_BULLET;
                    action.targetIndex = i;
                    makeAction(action);
                    action.action = DEATH;
                    action.senderType = PLAYER_BULLET;
                    makeAction(action);
                    break;
                }
            if (action.action == DEATH) // Our bullet is dead. No need in further checks
                break;
            for (int j = 0; j < bulletsCount; j++) // Collide bullet with all other bullets
                if (bullets[i].type != bullets[j].type &&
                    collide((GameObject*)&bullets[i], (GameObject*)&bullets[j]))
                {
                    action.action = DEATH;
                    action.senderType = ENEMY_BULLET;
                    action.senderIndex = i;
                    makeAction(action);
                    action.action = DEATH;
                    action.senderType = PLAYER_BULLET;
                    action.senderIndex = j;
                    makeAction(action);
                    break;
                }
            if (action.action != DEATH) // Our bullet is dead. It cant take actions
            {
                action = bullets[i].action(tick);
                makeAction(action);
            }
        }
        while (action.action != END_ACTION && action.action != DEATH);
        if (action.action == DEATH) // New bullet will be in position of the old one
            i--;
    }
}

void    GameCycle::actEnemies()
{
    Action  action;

    for (int i = 0; i < enemiesCount && enemiesCount; i++)
    {
        do
        {
            for (int j = 0; j < bulletsCount; j++) // Collide enemy with all player bullets
                if (bullets[j].type == PLAYER_BULLET &&
                    collide((GameObject*)enemies[i], (GameObject*)&bullets[j]))
                {
                    action.action = DAMAGE;
                    action.senderType = ENEMY;
                    action.senderIndex = i;
                    action.targetType = PLAYER_BULLET;
                    action.targetIndex = j;
                    makeAction(action);
                    action.action = DEATH;
                    action.senderType = PLAYER_BULLET;
                    action.senderIndex = j;
                    makeAction(action);
                    break;
                }
            action = enemies[i]->action(tick);
            makeAction(action);
        }
        while (action.action != END_ACTION && action.action != DEATH);
        if (action.action == DEATH) // New enemy will be in position of the old one
            i--;
    }
}

void    GameCycle::addEnemy()
{
    if (enemiesCount + 1 > MAX_ENEMIES_COUNT || enemiesCount + 1 > enemiesMax)
        return;
    if (enemies[enemiesCount])
        return;
    if ((enemies[enemiesCount] = new Enemy()))
    {
        int x = screenWidth;
        int y = rand() % (screenHeight - 3);
        enemies[enemiesCount]->shape.posX = x;
        enemies[enemiesCount]->shape.posY = y;
        enemies[enemiesCount]->dirX = 0;
        enemies[enemiesCount]->dirY = y;
        enemiesCount++;

    }
}

void    GameCycle::addBullet(int type, int x, int y, int dirX, int dirY)
{
    if (bulletsCount == 256)
        return ;
    bullets[bulletsCount].type = type;
    bullets[bulletsCount].shape.posX = x;
    bullets[bulletsCount].shape.posX = y;
    bullets[bulletsCount].dirX = dirX;
    bullets[bulletsCount].dirY = dirY;
}

void    GameCycle::removeBullet(int index)
{
    for (int i = index; i < bulletsCount - 1; i++)
        std::swap(bullets[i], bullets[i + 1]);
    bulletsCount--;
}

void    GameCycle::removeEnemy(Enemy *enemy, int index)
{
    for (int i = index; i < enemiesCount - 1; i++)
        std::swap(enemies[i], enemies[i + 1]);
    delete(enemies[enemiesCount]);
    enemies[enemiesCount] = nullptr;
    enemiesCount--;

}

void    GameCycle::draw()
{
    for (int i = 0; i < bulletsCount; i++)
        output((GameObject*)&bullets[i]);
    for (int i = 0; i < enemiesCount; i++)
        output((GameObject*)enemies[i]);
    output((GameObject*)&player);
}

void    GameCycle::output(GameObject *obj)
{
    for (int i = 0; i < obj->shape.height; i++)
        for (int j = 0; j < obj->shape.max_width; j++)
            mvaddch(obj->shape.posY + i, obj->shape.posX + j, obj->shape.str[i].c_str()[j]);
}

void    GameCycle::makeAction(Action action)
{
//    switch (action.senderType)
//    {
//        case PLAYER:
//            exitFlag = true;
//            break;
//        case ENEMY:
//            exitFlag = true;
//            break;
//        default:
//        std::cout << "Actor: " << action.senderType << std::endl;
//    }
    if (action.action == DEATH)
        exitFlag = true;
}

int     GameCycle::collide(GameObject *obj1, GameObject *obj2)
{
    // Fast collision detection between two rectangles
    int     x11 = obj1->shape.posX;
    int     x12 = obj1->shape.posX + obj1->shape.max_width;
    int     y11 = obj1->shape.posY;
    int     y12 = obj1->shape.posY + obj1->shape.height;

    int     x21 = obj2->shape.posX;
    int     x22 = obj2->shape.posX + obj2->shape.max_width;
    int     y21 = obj2->shape.posY;
    int     y22 = obj2->shape.posY + obj2->shape.height;

    if (y11 < y22 && y12 > y21 && x11 < x22 && x12 > x21)
        return (1);
    return (0);
    // todo: Test this; Implement more convenient collision detection algorithm.
}

int     GameCycle::startCycle()
{
    while (!exitFlag)
    {
        enemiesMax = score / 500 + 1;
        actPlayer();
        actBullets();
        actEnemies();
        clear();
        draw();
        refresh();
        tick++;
    }
    return score;
}
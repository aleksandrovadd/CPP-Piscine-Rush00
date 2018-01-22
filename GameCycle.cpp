//
// Created by Maksym Paziuk on 20.01.18.
//

#include "GameCycle.hpp"

GameCycle::GameCycle()
{
    score = 0;
    tick = 0;
    exitFlag = false;
    enemiesMax = 1;

    std::srand(std::time(0));
    initScreen();
    initEnemys();
    initBullets();
    initBackground();
}

GameCycle::GameCycle(GameCycle const &rhs)
{
    *this = rhs;
}

GameCycle& GameCycle::operator=(GameCycle const &src)
{
    this->player = src.player;
    this->enemies = src.enemies;
    this->enemiesCount = src.enemiesCount;
    this->enemiesMax = src.enemiesMax;
    this->bullets = src.bullets;
    this->bulletsCount = src.bulletsCount;
    this->score = src.score;
    this->tick = src.tick;
    this->exitFlag = src.exitFlag;
    for (int i = 0; i < MAX_STARS_COUNT; i++)
        this->st[i] = src.st[i];
    this->screenWidth = src.screenWidth;
    this->screenHeight = src.screenHeight;
    return *this;
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
    bullets = new Bullet*[MAX_BULLETS_COUNT];
    for (int i = 0; i < MAX_BULLETS_COUNT; i++)
        bullets[i] = nullptr;
}

void    GameCycle::initScreen()
{
    noecho();
    getmaxyx(stdscr, screenHeight, screenWidth);
    curs_set(false);
    timeout(0);
    cbreak();
    keypad(stdscr, true);
    player.screenWidth = screenWidth;
    player.screenHeight = screenHeight;
    if (has_colors())
    {
        use_default_colors();
        start_color();
        init_color(COLOR_YELLOW, 255, 191, 127);
        init_pair(1, COLOR_BLUE, -1);
        init_pair(2, COLOR_RED, -1);
        init_pair(3, COLOR_CYAN, -1);
        init_pair(4, COLOR_GREEN, -1);
        init_pair(5, COLOR_YELLOW, -1);
    }
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
                action.targetType = ENEMY;
                action.targetIndex = i;
                makeAction(action);
                break;
            }
        action = player.action(tick);
        makeAction(action);
    }
    while (action.action != END_ACTION);
}

void    GameCycle::actEnemies()
{
    Action  action;

    for (int i = 0; i < enemiesCount && enemiesCount; i++)
    {
        do
        {
            action = enemies[i]->action(tick);
            action.senderIndex = i;
            makeAction(action);
            if (action.action == DEATH)
            {
                i--;
                break;
            }
        }
        while (action.action != END_ACTION && action.action != DEATH && action.action != SHOOT);
    }
    refresh();
}

void    GameCycle::actBullet()
{
    Action  action;
    int     flag;

    for (int i = 0; i < bulletsCount && bulletsCount; i++)
    {
        flag = 0;
        do
        {
            if (collide((GameObject*)(&player), (GameObject*)bullets[i])
                && bullets[i]->type == ENEMY_BULLET)
            {
                action.senderType = PLAYER;
                action.senderIndex = -1;
                action.action = DAMAGE;
                action.targetType = ENEMY_BULLET;
                action.targetIndex = i;
                makeAction(action);
                removeBullet(i);
                i--;
                break;
            }
            for (int j = 0; j < enemiesCount; j++)
            {
                if (collide((GameObject*)enemies[j], (GameObject*)bullets[i])
                    && bullets[i]->type == PLAYER_BULLET)
                {
                    action.senderType = ENEMY;
                    action.senderIndex = j;
                    action.action = DAMAGE;
                    action.targetType = PLAYER_BULLET;
                    action.targetIndex = i;
                    makeAction(action);
                    removeBullet(i);
                    i--;
                    flag = 1;
                    break;
                }
            }
            if (!flag)
            {
                for (int j = 0; j < bulletsCount; j++)
                {
                    if (collide((GameObject*)bullets[i], (GameObject*)bullets[j])
                                && bullets[i]->type != bullets[j]->type)
                    {
                        removeBullet(i);
                        removeBullet(j);
                        if (i > j)
                            i--;
                        i--;
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag)
                break;
            action = bullets[i]->action(tick);
            action.senderIndex = i;
            makeAction(action);
        }
        while (action.action != END_ACTION && action.action != DEATH);
    }
}

void    GameCycle::addEnemy()
{
    if (enemiesCount + 1 > MAX_ENEMIES_COUNT || enemiesCount + 1 > enemiesMax)
        return;
    if (enemies[enemiesCount] != nullptr)
        return;
    enemies[enemiesCount] = new Enemy();
    int x = screenWidth;
    int y = rand() % (screenHeight - 3);
    enemies[enemiesCount]->shape.posX = x;
    enemies[enemiesCount]->shape.posY = y;
    enemiesCount++;
}

void    GameCycle::removeEnemy(int index)
{
    for (int i = index; i < enemiesCount - 1; i++)
        std::swap(enemies[i], enemies[i + 1]);
    enemiesCount--;
    if (enemies[enemiesCount])
        delete(enemies[enemiesCount]);
    enemies[enemiesCount] = nullptr;
}

void    GameCycle::addBullet(int type, int x, int y)
{
    if (bulletsCount + 1 > MAX_BULLETS_COUNT)
        return;
    if (bullets[bulletsCount] != nullptr)
        return;
    bullets[bulletsCount] = new Bullet;
    bullets[bulletsCount]->type = type;
    bullets[bulletsCount]->shape.posX = x;
    bullets[bulletsCount]->shape.posY = y;
    bulletsCount++;
}

void    GameCycle::removeBullet(int index)
{
    for (int i = index; i < bulletsCount - 1; i++)
        std::swap(bullets[i], bullets[i + 1]);
    bulletsCount--;
    if (bullets[bulletsCount])
        delete(bullets[bulletsCount]);
    bullets[bulletsCount] = nullptr;
}

void    GameCycle::draw()
{
    int g;
    for (int i = 0; i < MAX_STARS_COUNT; ++i)
    {
        g = rand()%5;
        attron(COLOR_PAIR(g));
        mvaddch(st[i].y, st[i].x, st[i].c);
        attroff(COLOR_PAIR(g));
    }
    for (int i = 0; i < bulletsCount; i++)
        output((GameObject*)bullets[i]);
    for (int i = 0; i < enemiesCount; i++)
        output((GameObject*)enemies[i]);
    output((GameObject*)&player);
}

void    GameCycle::output(GameObject *obj)
{
    int     n;

    if (obj->type == ENEMY)
        n = 2;
    else if (obj->type == PLAYER)
        n = 1;
    else if (obj->type == PLAYER_BULLET || obj->type == ENEMY_BULLET)
        n = 4;
    for (int i = 0; i < obj->shape.height; i++)
        for (int j = 0; j < obj->shape.max_width; j++)
            if (obj->shape.str[i].c_str()[j])
            {
                attron(COLOR_PAIR(n));
                mvaddch(obj->shape.posY + i, obj->shape.posX + j, obj->shape.str[i].c_str()[j]);
                attroff(COLOR_PAIR(n));
            }
}

void    GameCycle::makeAction(Action action)
{
    switch (action.action)
    {
        case END_ACTION:
            return;
        case DEATH:
            switch (action.senderType)
            {
                case PLAYER:
                    exitFlag = true;
                    break;
                case ENEMY:
                    score += 100;
                    removeEnemy(action.senderIndex);
                    break;
                default:
                    removeBullet(action.senderIndex);
                    break;
            }
            break;
        case DAMAGE:
            switch (action.senderType)
            {
                case PLAYER:
                    player.hit(bullets[action.targetIndex]->hp);
                    if (player.hp <= 0)
                        exitFlag = true;
                    break;
                case ENEMY:
                    enemies[action.senderIndex]->hit(bullets[action.targetIndex]->hp);
                    break;
            }
        case SHOOT:
            switch (action.senderType)
            {
                case PLAYER:
                    addBullet(PLAYER_BULLET,
                              player.shape.posX + player.shape.max_width + 1,
                              player.shape.posY + player.shape.height / 2);
                    break;
                case ENEMY:
                    addBullet(ENEMY_BULLET,
                              enemies[action.senderIndex]->shape.posX - 2,
                              enemies[action.senderIndex]->shape.posY + enemies[action.senderIndex]->shape.height / 2);
                    break;
            }
        default:
            return;
    }
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
}

int     GameCycle::startCycle()
{
    while (!exitFlag)
    {
        enemiesMax = score / 400 + 8;
        actPlayer();
        actEnemies();
        actBullet();
        clear();
        draw();
        mvprintw(1, 1, "SCORE: %d", score);
        mvprintw(2, 1, "HP: %d", player.hp);
        refresh();
        if (!(tick % 2000))
            addEnemy();
        if (!(tick % 500))
            moveBackground();
        tick++;
    }
    return score;
}
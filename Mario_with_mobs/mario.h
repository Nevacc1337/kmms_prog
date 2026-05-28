#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <vector>

#define MAP_WIDTH  80
#define MAP_HEIGHT 25

// ============================================================
// Класс GameObject — один игровой объект (блок, враг, монета)
// ============================================================
class GameObject
{
public:
    float x, y;
    float width, height;
    float vertSpeed;
    float horizSpeed;
    bool  isFly;
    char  type;     // '#' блок  '?' вопрос  '-' пусто  '+' финиш
                    // 'o' враг  '$' монета  '@' марио

    GameObject(float x, float y, float w, float h, char t);

    bool collidesWith(const GameObject& other) const;
    void drawOnMap(char map[MAP_HEIGHT][MAP_WIDTH + 1]) const;
};

// ============================================================
// Класс Game — вся игровая логика
// ============================================================
class Game
{
    char map[MAP_HEIGHT][MAP_WIDTH + 1];

    GameObject*             mario;
    std::vector<GameObject> bricks;
    std::vector<GameObject> moving;

    int level;
    int score;
    int maxLvl;

public:
    Game();
    ~Game();

    void run();

private:
    void processInput();
    void update();
    void render();

    void applyGravity(GameObject* obj);
    void moveEnemy(GameObject* obj);
    void checkMarioCollisions();
    void scrollMap(float dx);
    void playerDead();
    void loadLevel(int lvl);

    void clearMap();
    void drawScore();
    void hideCursor();
    void setCursor(int x, int y);
};

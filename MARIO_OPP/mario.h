#pragma once

#include <windows.h>

/* ── Карта ── */
#define MAP_WIDTH  80
#define MAP_HEIGHT 25

/* ── Физика ── */
constexpr float GRAVITY    =  0.3f;
constexpr float JUMP_SPEED = -10.0f;
constexpr float MOVE_SPEED =  12.0f;

constexpr char CHAR_MARIO = '@';
constexpr char CHAR_BRICK = '#';
constexpr char CHAR_GOAL  = '+';

/* ── Кирпичи ── */
constexpr int MAX_BRICKS = 10;


class Object {
public:
    float x, y;
    float width, height;
    float vertSpeed;
    BOOL  isFlying;
    char  symbol;

    Object(float x = 0, float y = 0,
           float w = 1, float h = 1,
           char symbol = ' ');

    /* Сталкивание */
    bool isCollision(const Object &other) const;

    /* Нарисовать себя на карте */
    void draw(char map[MAP_HEIGHT][MAP_WIDTH + 1]) const;
};


class Game {
public:
    Game();
    void run();

private:
    char   map[MAP_HEIGHT][MAP_WIDTH + 1];
    Object player;
    Object bricks[MAX_BRICKS];
    int    brickCount;
    int    level;

    void loadLevel(int lvl);
    void handleInput();
    void applyGravity();
    void scrollMap(float dx);
    void clearMap();
    void showMap();
    void hideCursor();
    void moveCursorTo(int x, int y);
};
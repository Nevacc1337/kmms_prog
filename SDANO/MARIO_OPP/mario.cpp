#include <cstdio>
#include <cmath>
#include <windows.h>
#include "mario.h"


/* ════════════════════════════════════════
   Object
════════════════════════════════════════ */

Object::Object(float x, float y, float w, float h, char symbol)
    : x(x), y(y), width(w), height(h),
      vertSpeed(0.0f), isFlying(TRUE), symbol(symbol)
{}

bool Object::isCollision(const Object &other) const
{
    return ((x + width)  > other.x) && (x < (other.x + other.width)) &&
           ((y + height) > other.y) && (y < (other.y + other.height));
}

void Object::draw(char map[MAP_HEIGHT][MAP_WIDTH + 1]) const
{
    int ix = (int)round(x),     iy = (int)round(y);
    int iw = (int)round(width), ih = (int)round(height);

    for (int col = ix; col < ix + iw; col++)
        for (int row = iy; row < iy + ih; row++)
            if (col >= 0 && col < MAP_WIDTH && row >= 0 && row < MAP_HEIGHT)
                map[row][col] = symbol;
}


/* ════════════════════════════════════════
   Методы
════════════════════════════════════════ */

Game::Game() : brickCount(0), level(1)
{
    loadLevel(level);
}

void Game::clearMap()
{
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++)
            map[row][col] = ' ';
        map[row][MAP_WIDTH] = '\0';
    }
}

void Game::showMap()
{
    for (int row = 0; row < MAP_HEIGHT; row++)
        printf("%s\n", map[row]);
}

void Game::hideCursor()
{
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize   = 1;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

void Game::moveCursorTo(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


/* ════════════════════════════════════════
   Уровень
════════════════════════════════════════ */

void Game::loadLevel(int lvl)
{
    player = Object(39, 10, 3, 3, CHAR_MARIO);

    if (lvl == 1) {
        brickCount = 6;
        bricks[0] = Object( 20, 20, 40,  5, CHAR_BRICK);
        bricks[1] = Object( 60, 15, 10, 10, CHAR_BRICK);
        bricks[2] = Object( 80, 20, 20,  5, CHAR_BRICK);
        bricks[3] = Object(120, 15, 10, 10, CHAR_BRICK);
        bricks[4] = Object(150, 20, 40,  5, CHAR_BRICK);
        bricks[5] = Object(210, 15, 10, 10, CHAR_GOAL);
    } else if (lvl == 2) {
        brickCount = 4;
        bricks[0] = Object( 20, 20, 40,  5, CHAR_BRICK);
        bricks[1] = Object( 80, 20, 15,  5, CHAR_BRICK);
        bricks[2] = Object(120, 15, 15, 10, CHAR_BRICK);
        bricks[3] = Object(160, 10, 15, 15, CHAR_GOAL);
    }
}


/* ════════════════════════════════════════
   Физика + кнопки 
════════════════════════════════════════ */

void Game::handleInput()
{
    if (!player.isFlying && GetKeyState(VK_SPACE) < 0)
        player.vertSpeed = JUMP_SPEED;

    if (GetKeyState('A') < 0) scrollMap(+MOVE_SPEED);
    if (GetKeyState('D') < 0) scrollMap(-MOVE_SPEED);
}

void Game::applyGravity()
{
    player.isFlying   = TRUE;
    player.vertSpeed += GRAVITY;
    player.y         += player.vertSpeed;

    for (int i = 0; i < brickCount; i++) {
        if (!player.isCollision(bricks[i]))
            continue;

        player.y        -= player.vertSpeed;
        player.vertSpeed = 0.0f;
        player.isFlying  = FALSE;

        if (bricks[i].symbol == CHAR_GOAL) {
            level = (level >= 2) ? 1 : level + 1;
            loadLevel(level);
            Sleep(1000);
        }
        break;
    }
}

void Game::scrollMap(float dx)
{
    player.x -= dx;
    for (int i = 0; i < brickCount; i++) {
        if (player.isCollision(bricks[i])) {
            player.x += dx;
            return;
        }
    }
    player.x += dx;

    for (int i = 0; i < brickCount; i++)
        bricks[i].x += dx;
}


/* ════════════════════════════════════════
   Цикл уровней
════════════════════════════════════════ */

void Game::run()
{
    system("color 9F");
    hideCursor();

    while (GetKeyState(VK_ESCAPE) >= 0)
    {
        handleInput();
        applyGravity();

        if (player.y > MAP_HEIGHT)
            loadLevel(level);

        clearMap();
        for (int i = 0; i < brickCount; i++)
            bricks[i].draw(map);
        player.draw(map);

        moveCursorTo(0, 0);
        showMap();

        Sleep(10);
    }
}


/* ════════════════════════════════════════
   MAIN 
════════════════════════════════════════ */

int main()
{
    Game game;
    game.run();
    return 0;
}
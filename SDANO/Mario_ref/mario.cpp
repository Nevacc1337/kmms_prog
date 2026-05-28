#include <cstdio>
#include <cmath>
#include <windows.h>
#include "mario.h"

/* ════════════════════════════════════════
   РЕНДЕР
════════════════════════════════════════ */

static char map[MAP_HEIGHT][MAP_WIDTH + 1];

void ClearMap()
{
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++)
            map[row][col] = ' ';
        map[row][MAP_WIDTH] = '\0';
    }
}

void DrawObject(Object obj)
{
    int x = (int)round(obj.x),    y = (int)round(obj.y);
    int w = (int)round(obj.width), h = (int)round(obj.height);

    for (int col = x; col < x + w; col++)
        for (int row = y; row < y + h; row++)
            if (col >= 0 && col < MAP_WIDTH && row >= 0 && row < MAP_HEIGHT)
                map[row][col] = obj.symbol;
}

void ShowMap()
{
    for (int row = 0; row < MAP_HEIGHT; row++)
        printf("%s\n", map[row]);
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize   = 1;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

void MoveCursorTo(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/* ════════════════════════════════════════
   ФИЗИКА
════════════════════════════════════════ */

BOOL IsCollision(Object a, Object b)
{
    return ((a.x + a.width)  > b.x) && (a.x < (b.x + b.width)) &&
           ((a.y + a.height) > b.y) && (a.y < (b.y + b.height));
}

void ApplyGravity(Object *obj, Object *bricks, int brickCount, int *level)
{
    obj->isFlying   = TRUE;
    obj->vertSpeed += GRAVITY;
    obj->y         += obj->vertSpeed;

    for (int i = 0; i < brickCount; i++) {
        if (!IsCollision(*obj, bricks[i]))
            continue;

        obj->y        -= obj->vertSpeed;
        obj->vertSpeed = 0.0f;
        obj->isFlying  = FALSE;

        if (bricks[i].symbol == CHAR_GOAL) {
            *level = (*level >= 2) ? 1 : *level + 1;
            Sleep(1000);
        }
        break;
    }
}

void ScrollMap(Object *player, Object *bricks, int brickCount, float dx)
{
    player->x -= dx;
    for (int i = 0; i < brickCount; i++) {
        if (IsCollision(*player, bricks[i])) {
            player->x += dx;
            return;
        }
    }
    player->x += dx;

    for (int i = 0; i < brickCount; i++)
        bricks[i].x += dx;
}

/* ════════════════════════════════════════
   УРОВНИ
════════════════════════════════════════ */

static Object MakeObject(float x, float y, float w, float h, char symbol)
{
    Object obj;
    obj.x         = x;
    obj.y         = y;
    obj.width     = w;
    obj.height    = h;
    obj.vertSpeed = 0.0f;
    obj.isFlying  = TRUE;
    obj.symbol    = symbol;
    return obj;
}

void LoadLevel(int lvl, Object *player, Object *bricks, int *brickCount)
{
    *player = MakeObject(39, 10, 3, 3, CHAR_MARIO);

    if (lvl == 1) {
        *brickCount = 6;
        bricks[0] = MakeObject( 20, 20, 40,  5, CHAR_BRICK);
        bricks[1] = MakeObject( 60, 15, 10, 10, CHAR_BRICK);
        bricks[2] = MakeObject( 80, 20, 20,  5, CHAR_BRICK);
        bricks[3] = MakeObject(120, 15, 10, 10, CHAR_BRICK);
        bricks[4] = MakeObject(150, 20, 40,  5, CHAR_BRICK);
        bricks[5] = MakeObject(210, 15, 10, 10, CHAR_GOAL);
    } else if (lvl == 2) {
        *brickCount = 4;
        bricks[0] = MakeObject( 20, 20, 40,  5, CHAR_BRICK);
        bricks[1] = MakeObject( 80, 20, 15,  5, CHAR_BRICK);
        bricks[2] = MakeObject(120, 15, 15, 10, CHAR_BRICK);
        bricks[3] = MakeObject(160, 10, 15, 15, CHAR_GOAL);
    }
}

/* ════════════════════════════════════════
   MAIN
════════════════════════════════════════ */

int main()
{
    int    level     = 1;
    int    prevLevel = 1;
    Object player;
    Object bricks[MAX_BRICKS];
    int    brickCount = 0;

    system("color 9F");
    HideCursor();
    LoadLevel(level, &player, bricks, &brickCount);

    while (GetKeyState(VK_ESCAPE) >= 0)
    {
        /* Ввод */
        if (!player.isFlying && GetKeyState(VK_SPACE) < 0)
            player.vertSpeed = JUMP_SPEED;
        if (GetKeyState('A') < 0) ScrollMap(&player, bricks, brickCount, +MOVE_SPEED);
        if (GetKeyState('D') < 0) ScrollMap(&player, bricks, brickCount, -MOVE_SPEED);

        /* Физика */
        ApplyGravity(&player, bricks, brickCount, &level);

        /* Упал за экран — перезагрузка */
        if (player.y > MAP_HEIGHT)
            LoadLevel(level, &player, bricks, &brickCount);

        /* Смена уровня */
        if (prevLevel != level) {
            LoadLevel(level, &player, bricks, &brickCount);
            prevLevel = level;
        }

        /* Рендер */
        ClearMap();
        for (int i = 0; i < brickCount; i++)
            DrawObject(bricks[i]);
        DrawObject(player);
        MoveCursorTo(0, 0);
        ShowMap();

        Sleep(7);
    }

    return 0;
}

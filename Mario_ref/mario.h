#pragma once

#include <windows.h>

/* ── Размеры карты ── */
#define MAP_WIDTH  80
#define MAP_HEIGHT 25

/* ── Физика ── */
constexpr float GRAVITY    =  0.08f;
constexpr float JUMP_SPEED = -1.5f;
constexpr float MOVE_SPEED =  2	.0f;

/* ── Символы ── */
constexpr char CHAR_MARIO = '@';
constexpr char CHAR_BRICK = '#';
constexpr char CHAR_GOAL  = '+';

/* ── Максимум кирпичей ── */
constexpr int MAX_BRICKS = 10;

struct Object {
    float x, y;
    float width, height;
    float vertSpeed;
    BOOL  isFlying;
    char  symbol;
};

/* render */
void ClearMap();
void DrawObject(Object obj);
void ShowMap();
void HideCursor();
void MoveCursorTo(int x, int y);

/* physics */
BOOL IsCollision(Object a, Object b);
void ApplyGravity(Object *obj, Object *bricks, int brickCount, int *level);
void ScrollMap(Object *player, Object *bricks, int brickCount, float dx);

/* levels */
void LoadLevel(int lvl, Object *player, Object *bricks, int *brickCount);

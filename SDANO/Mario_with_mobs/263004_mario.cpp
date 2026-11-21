#include "mario.h"

// ============================================================
// GameObject
// ============================================================

GameObject::GameObject(float x, float y, float w, float h, char t)
    : x(x), y(y), width(w), height(h),
      vertSpeed(0), horizSpeed(0.2f), isFly(true), type(t)
{}

bool GameObject::collidesWith(const GameObject& other) const
{
    return (x + width)  > other.x && x < (other.x + other.width) &&
           (y + height) > other.y && y < (other.y + other.height);
}

void GameObject::drawOnMap(char map[MAP_HEIGHT][MAP_WIDTH + 1]) const
{
    int ix = (int)round(x);
    int iy = (int)round(y);
    int iw = (int)round(width);
    int ih = (int)round(height);

    for (int i = ix; i < ix + iw; i++)
        for (int j = iy; j < iy + ih; j++)
            if (i >= 0 && i < MAP_WIDTH && j >= 0 && j < MAP_HEIGHT)
                map[j][i] = type;
}

// ============================================================
// Game — конструктор / деструктор
// ============================================================

Game::Game() : mario(nullptr), level(1), score(0), maxLvl(3)
{
    hideCursor();
    loadLevel(level);
}

Game::~Game()
{
    delete mario;
}

// ============================================================
// Game — главный цикл
// ============================================================

void Game::run()
{
    do {
        processInput();
        update();
        render();
        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);
}

// ============================================================
// Game — ввод
// ============================================================

void Game::processInput()
{
    if (!mario->isFly && GetKeyState(VK_SPACE) < 0)
        mario->vertSpeed = -1.0f;

    if (GetKeyState('A') < 0) scrollMap( 1.0f);
    if (GetKeyState('D') < 0) scrollMap(-1.0f);
}

// ============================================================
// Game — обновление
// ============================================================

void Game::update()
{
    if (mario->y > MAP_HEIGHT) playerDead();

    applyGravity(mario);
    checkMarioCollisions();

    for (int i = 0; i < (int)moving.size(); i++)
    {
        applyGravity(&moving[i]);
        moveEnemy(&moving[i]);

        if (moving[i].y > MAP_HEIGHT)
        {
            moving.erase(moving.begin() + i);
            i--;
        }
    }
}

// ============================================================
// Game — рисование
// ============================================================

void Game::render()
{
    clearMap();

    for (auto& b : bricks)  b.drawOnMap(map);
    for (auto& m : moving)  m.drawOnMap(map);
    mario->drawOnMap(map);

    drawScore();

    setCursor(0, 0);
    for (int j = 0; j < MAP_HEIGHT; j++)
        printf("%s\n", map[j]);
}

// ============================================================
// Game — физика
// ============================================================

void Game::applyGravity(GameObject* obj)
{
    obj->isFly      = true;
    obj->vertSpeed += 0.05f;
    obj->y         += obj->vertSpeed;

    for (auto& brick : bricks)
    {
        if (!obj->collidesWith(brick)) continue;

        if (obj->vertSpeed > 0)
            obj->isFly = false;

        if (brick.type == '?' && obj->vertSpeed < 0 && obj == mario)
        {
            brick.type = '-';
            GameObject coin(brick.x, brick.y - 3, 3, 2, '$');
            coin.vertSpeed = -0.7f;
            moving.push_back(coin);
        }

        obj->y        -= obj->vertSpeed;
        obj->vertSpeed = 0;

        if (brick.type == '+')
        {
            level++;
            if (level > maxLvl) level = 1;
            system("color 2F");
            Sleep(500);
            loadLevel(level);
        }
        break;
    }
}

void Game::moveEnemy(GameObject* obj)
{
    obj->x += obj->horizSpeed;

    for (auto& brick : bricks)
    {
        if (obj->collidesWith(brick))
        {
            obj->x         -= obj->horizSpeed;
            obj->horizSpeed = -obj->horizSpeed;
            return;
        }
    }

    if (obj->type == 'o')
    {
        GameObject tmp = *obj;
        applyGravity(&tmp);
        if (tmp.isFly)
        {
            obj->x         -= obj->horizSpeed;
            obj->horizSpeed = -obj->horizSpeed;
        }
    }
}

void Game::checkMarioCollisions()
{
    for (int i = 0; i < (int)moving.size(); i++)
    {
        if (!mario->collidesWith(moving[i])) continue;

        if (moving[i].type == 'o')
        {
            bool jumpedOn = mario->isFly
                         && mario->vertSpeed > 0
                         && mario->y + mario->height < moving[i].y + moving[i].height * 0.5f;

            if (jumpedOn)
            {
                score += 50;
                moving.erase(moving.begin() + i);
                i--;
            }
            else
            {
                playerDead();
            }
        }
        else if (moving[i].type == '$')
        {
            score += 100;
            moving.erase(moving.begin() + i);
            i--;
        }
    }
}

void Game::scrollMap(float dx)
{
    mario->x -= dx;
    for (auto& b : bricks)
        if (mario->collidesWith(b)) { mario->x += dx; return; }
    mario->x += dx;

    for (auto& b : bricks)  b.x += dx;
    for (auto& m : moving)  m.x += dx;
}

void Game::playerDead()
{
    system("color 4F");
    Sleep(500);
    loadLevel(level);
}

// ============================================================
// Game — загрузка уровня
// ============================================================

void Game::loadLevel(int lvl)
{
    system("color 9F");
    bricks.clear();
    moving.clear();
    score = 0;

    delete mario;
    mario = new GameObject(5, 17, 3, 3, '@');

    if (lvl == 1)
    {
        bricks.push_back({  0, 20, 40,  5, '#'});
        bricks.push_back({ 10,  9,  5,  2, '?'});
        bricks.push_back({ 20,  9,  5,  2, '?'});
        bricks.push_back({ 45, 15, 20,  3, '#'});
        bricks.push_back({ 47,  7,  5,  2, '-'});
        bricks.push_back({ 52,  7,  5,  2, '?'});
        bricks.push_back({ 57,  7,  5,  2, '-'});
        bricks.push_back({ 70, 17, 15,  5, '#'});
        bricks.push_back({ 90, 20, 25,  5, '#'});
        bricks.push_back({120, 15, 10,  5, '#'});
        bricks.push_back({140, 20, 30,  5, '#'});
        bricks.push_back({180, 14, 10, 11, '+'});

        moving.push_back({ 15, 18, 3, 2, 'o'});
        moving.push_back({ 50, 13, 3, 2, 'o'});
    }
    else if (lvl == 2)
    {
        bricks.push_back({  0, 20, 35,  5, '#'});
        bricks.push_back({ 10,  9,  5,  2, '?'});
        bricks.push_back({ 40, 15, 20,  5, '#'});
        bricks.push_back({ 65, 20, 30,  5, '#'});
        bricks.push_back({ 70, 10,  5,  2, '?'});
        bricks.push_back({100, 14, 20,  5, '#'});
        bricks.push_back({125, 20, 30,  5, '#'});
        bricks.push_back({160, 14, 10, 11, '+'});

        moving.push_back({ 12, 18, 3, 2, 'o'});
        moving.push_back({ 42, 13, 3, 2, 'o'});
        moving.push_back({ 67, 18, 3, 2, 'o'});
        moving.push_back({102, 12, 3, 2, 'o'});
        moving.push_back({127, 18, 3, 2, 'o'});
        moving.push_back({140, 18, 3, 2, 'o'});
    }
    else if (lvl == 3)
    {
        bricks.push_back({  0, 20, 30,  5, '#'});
        bricks.push_back({ 35, 17, 15,  5, '#'});
        bricks.push_back({ 55, 13, 15,  5, '#'});
        bricks.push_back({ 75,  9, 15,  5, '#'});
        bricks.push_back({100, 13, 15,  5, '#'});
        bricks.push_back({120, 17, 15,  5, '#'});
        bricks.push_back({140, 14, 10, 11, '+'});

        moving.push_back({ 10, 18, 3, 2, 'o'});
        moving.push_back({ 36, 15, 3, 2, 'o'});
        moving.push_back({ 56, 11, 3, 2, 'o'});
        moving.push_back({ 76,  7, 3, 2, 'o'});
        moving.push_back({101, 11, 3, 2, 'o'});
        moving.push_back({121, 15, 3, 2, 'o'});
    }
}

// ============================================================
// Game — вспомогательные
// ============================================================

void Game::clearMap()
{
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++)
            map[j][i] = ' ';
        map[j][MAP_WIDTH] = '\0';
    }
}

void Game::drawScore()
{
    char buf[30];
    sprintf(buf, "Score: %d", score);
    int len = strlen(buf);
    for (int i = 0; i < len; i++)
        map[1][i + 5] = buf[i];
}

void Game::hideCursor()
{
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize   = 1;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

void Game::setCursor(int x, int y)
{
    COORD c; c.X = x; c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// ============================================================
// main
// ============================================================

int main()
{
    Game game;
    game.run();
    return 0;
}

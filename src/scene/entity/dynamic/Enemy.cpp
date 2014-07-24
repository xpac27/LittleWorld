#include "Enemy.h"

using namespace std;

Enemy::Enemy(World *w, float x, float z, float s) : Dynamic(w, s)
{
    speed = 120.f;

    position.x = 512.f;
    position.y = 0.f;
    position.z = 512.f;
}

void Enemy::update(float time)
{
    if (!isCanMove() && ODDS(1))
    {
        float x = RAND_FLOAT * 1200 - 600 + position.x;
        float y = RAND_FLOAT * 1200 - 600 + position.z;

        setPath(world->getPath(&position, x, y, getSize()));
    }

    move(time);
}


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
    if (!isCanMove() && sf::Randomizer::Random(0, 50) == 0)
    {
        float x = sf::Randomizer::Random(position.x - 600, position.x + 600);
        float y = sf::Randomizer::Random(position.z - 600, position.z + 600);

        setPath(world->getPath(&position, x, y, getSize()));
    }

    move(time);
}


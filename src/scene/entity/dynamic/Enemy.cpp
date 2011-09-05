#include "Enemy.h"

using namespace std;

Enemy::Enemy(World *W, float s) : Dynamic(W, s)
{
    speed = 120.f;
}

void Enemy::update(float time)
{
    if (!isCanMove() && sf::Randomizer::Random(0, 50) == 0)
    {
        setPath
        (
            sf::Randomizer::Random(position.x - 600, position.x + 600),
            sf::Randomizer::Random(position.z - 600, position.z + 600)
        );
    }
    move(time);
}


#include "Enemy.h"

using namespace std;

Enemy::Enemy(World *w, float s) : Dynamic(w, s)
{
    speed = 120.f;
}

void Enemy::update(float time)
{
    if (!isCanMove() && sf::Randomizer::Random(0, 50) == 0)
    {
        // TODO
        //setPath
        //(
            //sf::Randomizer::Random(position.x - 600, position.x + 600),
            //sf::Randomizer::Random(position.z - 600, position.z + 600)
        //);
    }
    move(time);
}


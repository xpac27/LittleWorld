#include "Enemy.h"

using namespace std;

Enemy::Enemy(World *W) : DynamicObject(W, 32.f, false)
{
    speed = 120.f;

    setSize(32.f);
}

void Enemy::draw()
{
    glColor4f(1.f, 0.f, 0.f, 1.f);

    Object::draw();
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


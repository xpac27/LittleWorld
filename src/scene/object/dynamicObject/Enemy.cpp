#include "Enemy.h"

using namespace std;

Enemy::Enemy(World *W) : DynamicObject(W, 32.f, true)
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
            sf::Randomizer::Random(position.x - 300, position.x + 300),
            sf::Randomizer::Random(position.y - 300, position.y + 300)
        );
    }
    move(time);
}


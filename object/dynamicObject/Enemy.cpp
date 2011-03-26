#include "Enemy.h"

using namespace std;
using namespace sf;

Enemy::Enemy(World *w) : DynamicObject(w, 16.f)
{
    speed = 60.f;

    position.set(0.f, 0.f);
    setSize(32.f);
}

void Enemy::draw()
{
    glColor4f(1.f, 0.f, 0.f, 1.f);

    Object::draw();
}

void Enemy::update(float time)
{
    if (!isCanMove() && Randomizer::Random(0, 50) == 0)
    {
        Position p(Randomizer::Random(position.x - 300, position.x + 300), Randomizer::Random(position.y - 300, position.y + 300));
        setPath(&p);
    }
    move(time);
}


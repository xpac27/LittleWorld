#include "Player.h"

using namespace boost;
using namespace sf;

Player::Player(World *w) : DynamicObject(w, 32.f)
{
    speed = 100.f;

    position.set(0.f, 0.f);
    destination.set(0.f, 0.f);
    setSize(64.f);

    world->ON_MOUSE_LEFT_DOWN.connect(bind(&Player::onMouseLeftDown, this));
}

void Player::onMouseLeftDown()
{
    destination.set(world->mouseX, world->mouseY);
    direction.set(&position, &destination);
}

void Player::draw()
{
    glColor4f(1.f, 0.8f, 0.f, 1.f);

    Object::draw();
}

void Player::update(float time)
{
    if (position.getDistanceTo(&destination) > 2.f)
    {
        move(time);
    }
}


#include "Player.h"

using namespace boost;
using namespace sf;

Player::Player(World *w) : DynamicObject(w, 32.f)
{
}

void Player::init()
{
    x      = 0.f;
    y      = 0.f;
    size   = 64.f;
    speed  = 100.f;
    destination[0] = x;
    destination[1] = y;

    world->ON_MOUSE_LEFT_DOWN.connect(bind(&Player::onMouseLeftDown, this));

    Object::init();
}

void Player::onMouseLeftDown()
{
    destination[0] = world->mouseX;
    destination[1] = world->mouseY;
}

void Player::draw()
{
    glColor4f(1.f, 0.8f, 0.f, 1.f);

    Object::draw();
}

void Player::update(float time)
{
    if ((x > destination[0] + 1) || (x < destination[0] - 1))
    {
        x += ((x < destination[0]) ? speed : -speed) * time;
    }
    if ((y > destination[1] + 1) || (y < destination[1] - 1))
    {
        y += ((y < destination[1]) ? speed : -speed) * time;
    }
}


#include "Player.h"

using namespace std;

Player::Player(World *W) : DynamicObject(W, 64.f, true)
{
    speed = 200.f;

    position.x = 512.f;
    position.z = 512.f;

    setSize(128.f);
}

void Player::onNotify(unsigned const int type)
{
    if (type == World::ON_MOUSE_LEFT_DOWN)
    {
        setPath(world->mouseX, world->mouseY);
    }
}

void Player::draw()
{
    glColor4f(1.f, 0.8f, 0.f, 1.f);

    Object::draw();
}

void Player::update(float time)
{
    move(time);
}


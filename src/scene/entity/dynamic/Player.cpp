#include "Player.h"

using namespace std;

Player::Player(World *w, float s) : Dynamic(w, s)
{
    speed = 200.f;

    position.x = 512.f;
    position.y = 0.f;
    position.z = 512.f;
}

void Player::onNotify(unsigned const int type)
{
    if (type == Notifications::ON_MOUSE_LEFT_DOWN)
    {
        setPath(world->getPath(&position, world->getMouseX(), world->getMouseY(), getSize()));
    }
}

void Player::update(float time)
{
    move(time);
}


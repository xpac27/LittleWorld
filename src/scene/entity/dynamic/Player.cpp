#include "Player.h"

using namespace std;

Player::Player(World *W, float s) : Dynamic(W, s)
{
    speed = 200.f;

    position.x = 512.f;
    position.z = 512.f;
}

void Player::onNotify(unsigned const int type)
{
    if (type == World::ON_MOUSE_LEFT_DOWN)
    {
        setPath(world->mouseX, world->mouseY);
    }
}

void Player::update(float time)
{
    move(time);
}


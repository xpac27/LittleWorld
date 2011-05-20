#include "Player.h"

using namespace boost;
using namespace std;

Player::Player(World *W) : DynamicObject(W, 32.f, false)
{
    speed = 100.f;

    position.x = 512.f;
    position.y = 512.f;

    setSize(64.f);

    world->ON_MOUSE_LEFT_DOWN.connect(bind(&Player::onMouseLeftDown, this));
}

void Player::onMouseLeftDown()
{
    // TODO find a way to not create a new vector each time
    Vector2 p(world->mouseX, world->mouseY);
    setPath(&p);
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


#include "Player.h"

using namespace boost;
using namespace sf;
using namespace std;

Player::Player(World *w) : DynamicObject(w, 32.f)
{
    speed = 100.f;

    position.set(256.f, 256.f);
    setSize(64.f);

    world->ON_MOUSE_LEFT_DOWN.connect(bind(&Player::onMouseLeftDown, this));
}

void Player::onMouseLeftDown()
{
    //setDestination(world->mouseX, world->mouseY);
    // TODO pass a pathfinder pointer to dynamicObjects
    setPath(world->getPath(position.x, position.y, world->mouseX, world->mouseY, getSize()));
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


#include "Player.h"

using namespace boost;
using namespace sf;

Player::Player(World *w) : DynamicObject(w)
{
}

void Player::init()
{
    x     = 400.f;
    y     = 300.f;
    z     = 2.f;
    size  = 10.f;
    speed = 80.f;
    destination[0] = x;
    destination[1] = y;

    world->ON_MOUSE_LEFT_DOWN.connect(bind(&Player::onMouseLeftDown, this));
}

void Player::onMouseLeftDown()
{
    std::cout << "player - mouse left pressed (" << world->mouseX << "x" << world->mouseY << ")" << std::endl;

    destination[0] = world->mouseX;
    destination[1] = world->mouseY;
}

void Player::draw()
{
    glColor4f(1.f, 1.f, 0.f, 1.f);

    glBegin(GL_QUADS);

        glVertex2f(-size, -size);
        glVertex2f(-size,  size);
        glVertex2f( size,  size);
        glVertex2f( size, -size);

    glEnd();
}

void Player::update(float time)
{
    x += speed * time * Randomizer::Random(-1.f, 1.f);
    y += speed * time * Randomizer::Random(-1.f, 1.f);

    x += ((x < destination[0]) ? speed : -speed) * time;
    y += ((y < destination[1]) ? speed : -speed) * time;
}


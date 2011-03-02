#include "Player.h"

using namespace boost;
using namespace sf;

Player::Player(World *w) : DynamicObject(w)
{
}

void Player::init()
{
    x     = 400;
    y     = 300;
    size  = 10;
    speed = 50;

    world->ON_TEST.connect(bind(&Player::onTest, this));
}

void Player::onTest()
{
    // TODO create a log static function in a Util class that uses iostream
}

void Player::draw()
{
    glColor4f(1.f, 1.f, 0.f, 0.8f);

    glPushMatrix();

        glTranslatef(x, y, 0.0f);

        glBegin(GL_QUADS);

            glVertex2f(-size, -size);
            glVertex2f(-size,  size);
            glVertex2f( size,  size);
            glVertex2f( size, -size);

        glEnd();

    glPopMatrix();
}

void Player::update(float time)
{
    x += speed * time * Randomizer::Random(-1.f, 1.f);
    y += speed * time * Randomizer::Random(-1.f, 1.f);
}



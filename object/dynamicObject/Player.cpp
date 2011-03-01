#include "Player.h"

#include <SFML/Graphics.hpp>

Player::Player()
{
}

void Player::init()
{
    this->x     = 400;
    this->y     = 300;
    this->size  = 10;
    this->speed = 50;
}

void Player::draw()
{
    glColor4f(1.f, 1.f, 0.f, 0.8f);

    glPushMatrix();

        glTranslatef(this->x, this->y, 0.0f);

        glBegin(GL_QUADS);

            glVertex2f(-this->size, -this->size);
            glVertex2f(-this->size,  this->size);
            glVertex2f( this->size,  this->size);
            glVertex2f( this->size, -this->size);

        glEnd();

    glPopMatrix();
}

void Player::update(float time)
{
    this->x += speed * time * sf::Randomizer::Random(-1.f, 1.f);
    this->y += speed * time * sf::Randomizer::Random(-1.f, 1.f);
}


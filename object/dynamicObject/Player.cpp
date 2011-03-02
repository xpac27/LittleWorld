#include "Player.h"

Player::Player(World *w) : DynamicObject(w)
{
}

void Player::init()
{
    this->x     = 400;
    this->y     = 300;
    this->size  = 10;
    this->speed = 50;

    this->world->ON_TEST.connect(boost::bind(&Player::prout, this));
}

void Player::prout()
{
    std::cout << "prout" << std::endl;
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



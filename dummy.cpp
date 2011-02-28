#include <SFML/Graphics.hpp>
#include "Dummy.h"

Dummy::Dummy()
{
    x = 400.f;
    y = 300.f;
    speed = sf::Randomizer::Random(50.f, 500.f);
}

void Dummy::draw()
{
    glPushMatrix();

    glTranslatef(x, y, 0.0f);

    glColor4f(1.f, 0.f, 0.f, 0.2f);

    glBegin(GL_QUADS);
        glVertex2f(-5.f, -5.f);
        glVertex2f(-5.f,  5.f);
        glVertex2f( 5.f,  5.f);
        glVertex2f( 5.f, -5.f);
    glEnd();

    glPopMatrix();
}

void Dummy::update(double time)
{
    x += speed * time * sf::Randomizer::Random(-1.f, 1.f);
    y += speed * time * sf::Randomizer::Random(-1.f, 1.f);
}


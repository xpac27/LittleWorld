#include "Tile.h"

Tile::Tile(World *w, float positionX, float positionY) : StaticObject(w)
{
    x = positionX;
    y = positionY;
    z = 1.f;
    size = 16.f;
}

void Tile::init()
{
}

void Tile::draw()
{
    glColor4f(0.2f, 0.2f, 0.2f, 1.f);

    glBegin(GL_QUADS);

        glVertex2f(-size, -size);
        glVertex2f(-size,  size);
        glVertex2f( size,  size);
        glVertex2f( size, -size);

    glEnd();

    glColor4f(0.4f, 0.4f, 0.4f, 1.f);

    glBegin(GL_LINES);

        glVertex2f(-size, -size);
        glVertex2f(-size,  size);

        glVertex2f(-size,  size);
        glVertex2f( size,  size);

        glVertex2f( size,  size);
        glVertex2f( size, -size);

        glVertex2f( size, -size);
        glVertex2f(-size, -size);

    glEnd();
}


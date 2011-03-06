#include "Tile.h"

Tile::Tile(World *w, float positionX, float positionY, float h) : StaticObject(w, h)
{
    x    = positionX;
    y    = positionY;
    size = 128.f;
}

void Tile::draw()
{
    glColor4f(0.9f, 0.9f, 0.9f, 1.f);

    Object::draw();
}


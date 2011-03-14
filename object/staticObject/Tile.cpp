#include "Tile.h"

Tile::Tile(World *w, float x, float y, float h) : StaticObject(w, h)
{
    position.set(x, y);
    setSize(128.f);
}

void Tile::draw()
{
    if (getHeight() == 0)
    {
        glColor4f(0.9f, 0.9f, 0.9f, 1.f);
    }
    else
    {
        glColor4f(0.8f, 0.8f, 0.8f, 1.f);
    }

    Object::draw();
}


#include "Decor.h"

Decor::Decor(World *W, float x, float z, float s, bool w) : Static(W, s)
{
    position.x = x;
    position.y = 0.f;
    position.z = z;

    walkable = w;
}

bool Decor::isWalkable() { return walkable; }


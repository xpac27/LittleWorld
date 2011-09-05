#include "Tile.h"

Tile::Tile(World *W, float x, float z, float s, bool w) : Static(W, s)
{
    position.x = x;
    position.y = 0.f;
    position.z = z;

    walkable = w;
}

bool Tile::isWalkable() { return walkable; }


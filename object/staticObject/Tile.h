#ifndef DEF_TILE
#define DEF_TILE

#include "../StaticObject.h"
#include "../../World.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class Tile : public StaticObject
{
    public:

        Tile(World *w, float x, float y, float h);

        virtual void draw();
};

#endif


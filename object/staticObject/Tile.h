#ifndef DEF_TILE
#define DEF_TILE

#include "../StaticObject.h"
#include "../../World.h"

#include <SFML/Graphics.hpp>

class Tile : public StaticObject
{
    public:

        Tile(World *w, float positionX, float positionY, float h);

        virtual void draw();
};

#endif


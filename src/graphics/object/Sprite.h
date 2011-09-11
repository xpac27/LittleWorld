#ifndef DEF_SPRITE
#define DEF_SPRITE

#include "../Object.h"
#include "../../resources/Structs.h"

#include <iostream>
#include <SFML/Graphics.hpp>

// TODO Have an instance of obj instead of the struct and the long constructor

class Sprite : public Object
{
    public:

        Sprite(Entity *e, float size, float height, float red, float green, float blue, float alpha);

        virtual void draw();
        virtual void outline();


    private:

        unsigned int totalVertex;
        unsigned int totalIndex;

        Vertex vertexes[4];
        int index[6];
};

#endif


#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "util/Position.h"

#include <SFML/Graphics.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <iostream>

class World;

class Object
{
    public:

        Object(World *w, float h);

        virtual void init();
        virtual void draw();

        void setSize(float s);
        void setPosition(float x, float y);
        void drawShadow(float lightX, float lightY);

        float getX();
        float getY();
        float getHeight();
        float getSize();
        float getIndex();

        bool touched;


    protected:

        World *world;

        Position position;


    private:

        float index;
        float height;
        float size;
        float alfSize;
        float quarterSize;
};

#endif


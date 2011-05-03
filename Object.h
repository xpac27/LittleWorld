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
        virtual void drawOutline();

        void setSize(float s);
        void setPosition(float x, float y);
        void drawShadow(float lightX, float lightY);

        float getX();
        float getY();
        float getHeight();
        float getSize();
        float getIndex();


    protected:

        World *world;

        Position position;


    private:

        float index;
        float height;
        float size;
        float alfSize;
        float quarterSize;

        bool doesEdgeCastShadow(float px1, float py1, float px2, float py2, float lx1, float ly2);
        float dotProduct(float x1, float y1, float x2, float y2);
};

#endif


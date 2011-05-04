#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "util/Position.h"

#include <SFML/Graphics.hpp>
#include <boost/bind.hpp>
#include <list>
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
        void drawShadow(float lx, float ly, std::list<Object*> objects);

        float getX();
        float getY();
        float getHeight();
        float getSize();
        float getIndex();

        Object operator<(Object &o);


    protected:

        World *world;

        Position position;


    private:

        float index;
        float height;
        float size;
        float alfSize;
        float quarterSize;

        void drawEdgeShadow(float edge[4], float lx, float ly);
        bool doesEdgeCastShadow(float px1, float py1, float px2, float py2, float lx1, float ly2);
        float dotProduct(float x1, float y1, float x2, float y2);
};

#endif


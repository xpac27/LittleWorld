#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "util/Position.h"
#include "util/Segment.h"
#include "util/Quad.h"

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

        Quad getEdgeShadow(Segment *edge, float lx, float ly);

        Object operator<(Object &o);


    protected:

        World *world;

        Position position;


    private:

        float index;
        float height;
        float size;

        Quad faceLeft;
        Quad faceRight;
        Quad faceTop;

        Segment edgeBL;
        Segment edgeBR;
        Segment edgeTL;
        Segment edgeTR;

        bool doesEdgeCastShadow(Segment *edge, float lx, float ly);
};

#endif


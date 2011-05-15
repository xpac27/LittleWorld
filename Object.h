#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "util/IntersectionFunctions.h"
#include "util/ContainFunctions.h"
#include "util/Position.h"
#include "util/Segment.h"
#include "util/Quad.h"
#include "util/Vector2.h"

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
        void updateShadow(float lx, float ly);
        void drawShadow();
        void drawWallShadows(std::list<Object*> objects);
        void drawWallShadow(Quad *shadow, float h);


        float getX();
        float getY();
        float getHeight();
        float getSize();
        float getIndex();

        Quad getEdgeShadow(Segment *edge, float lx, float ly);

        Segment edgeBL;
        Segment edgeBR;
        Segment edgeTL;
        Segment edgeTR;

        Quad faceLeft;
        Quad faceRight;
        Quad faceTop;

        Quad shadowBR;
        Quad shadowBL;
        Quad shadowTR;
        Quad shadowTL;

        bool edgeBRCast;
        bool edgeBLCast;
        bool edgeTRCast;
        bool edgeTLCast;


    protected:

        World *world;

        Position position;


    private:

        float index;
        float height;
        float size;

        bool doesEdgeCastShadow(Segment *edge, float lx, float ly);
};

class ObjectComparer
{
    public:

        bool operator() (Object *o1, Object *o2)
        {
            return (*o1).getY() < (*o2).getY();
        }
};

#endif


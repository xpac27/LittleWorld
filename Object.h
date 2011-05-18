#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "util/geometry/IntersectionFunctions.h"
#include "util/geometry/ContainFunctions.h"
#include "util/primitive/Segment.h"
#include "util/primitive/Quad.h"
#include "util/primitive/Vector2.h"
#include "util/Position.h"

#include <SFML/Graphics.hpp>
#include <boost/bind.hpp>
#include <list>
#include <iostream>

class World;

class Object
{
    public:

        Object(World *W, float h, bool s);

        virtual void init();
        virtual void draw();
        virtual void drawOutline();

        void setSize(float s);
        void setPosition(float x, float y);
        void setCastShadow(bool v);
        void updateShadows(float lx, float ly);
        void drawShadow();
        void drawWallShadows(std::list<Object*> objects);
        void drawWallShadow(Quad *shadow, float h);
        Quad updateShadow(Quad *shadow, Segment *edge, float lx, float ly);

        bool shadowEnabled();

        bool edgeCastShadowBR;
        bool edgeCastShadowBL;
        bool edgeCastShadowTR;
        bool edgeCastShadowTL;

        float getX();
        float getY();
        float getHeight();
        float getSize();
        float getIndex();

        Segment* getBaseEdgeBL();
        Segment* getBaseEdgeBR();
        Segment* getBaseEdgeTL();
        Segment* getBaseEdgeTR();

        Quad* getShadowBR();
        Quad* getShadowBL();
        Quad* getShadowTR();
        Quad* getShadowTL();


    protected:

        World *world;

        Position position;


    private:

        bool edgeCastShadow(Segment *edge, float lx, float ly);

        bool shadow;

        float index;
        float height;
        float size;

        Quad faceL;
        Quad faceR;
        Quad faceT;
        Quad shadowBR;
        Quad shadowBL;
        Quad shadowTR;
        Quad shadowTL;
};

// TODO put this somewhere else
class ObjectComparer
{
    public:

        bool operator() (Object *o1, Object *o2)
        {
            return (((*o1).getY() + (*o1).getY()) / 2.f) < (((*o2).getY() + (*o2).getY()) / 2.f);
        }
};

#endif


#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "Light.h"
#include "../math/IntersectionFunctions.h"
#include "../math/ContainFunctions.h"
#include "../graphics/Segment.h"
#include "../graphics/Polygon.h"
#include "../graphics/Vector2.h"

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

class World;

class Object
{
    public:

        Object(World *W, float h, bool s);

        virtual void init();
        virtual void draw();
        virtual void outline();

        void setSize(float s);
        void setPosition(float x, float y);
        void setCastShadow(bool v);
        void updateShadows(Light *l);
        void drawShadow();
        void drawSelfShadows(std::list<Object*> *objects);
        void drawWallShadow(Polygon *shadow, float h);
        void updateShadow(Polygon *shadow, Segment *edge, Light *light);

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

        Polygon* getFace(unsigned int f);
        Polygon* getShadowBR();
        Polygon* getShadowBL();
        Polygon* getShadowTR();
        Polygon* getShadowTL();


    protected:

        World *world;

        Vector2 position;


    private:

        bool edgeCastShadow(Segment *edge, Light *light);

        Polygon* getFaceTop();

        bool shadow;

        float index;
        float height;
        float size;

        Polygon faceL;
        Polygon faceR;
        Polygon faceT;
        Polygon faceT_high;
        Polygon shadowBR;
        Polygon shadowBL;
        Polygon shadowTR;
        Polygon shadowTL;
};

#endif


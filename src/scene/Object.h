#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "Light.h"
#include "../math/IntersectionFunctions.h"
#include "../math/ContainFunctions.h"
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

        bool shadowEnabled();

        float getX();
        float getY();
        float getHeight();
        float getSize();


    protected:

        World *world;

        Vector2 position;


    private:

        Polygon* getFaceTop();

        bool shadow;

        float index;
        float height;
        float size;

        Polygon faceL;
        Polygon faceR;
        Polygon faceT;
};

#endif


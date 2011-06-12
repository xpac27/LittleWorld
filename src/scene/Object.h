#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "Light.h"
#include "../graphics/Polygon.h"
#include "../graphics/Point.h"
#include "../math/Vector3.h"

#include <SFML/Graphics.hpp>
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
        void setPosition(float x, float y, float z);
        void updateShadows(Light *l);
        void drawShadow(Light *l);

        bool shadowEnabled();

        float getX();
        float getY();
        float getZ();
        float getHeight();
        float getSize();


    protected:

        World *world;

        Vector3 position;


    private:

        bool shadow;

        float height;
        float size;

        Point p1, p2, p3, p4, p5, p6, p7, p8;

        Polygon shape;
};

#endif


#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "Light.h"
#include "../graphics/Polygon.h"
#include "../math/Vector3.h"

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
        virtual void drawOutline();

        void setSize(float s);
        void setPosition(float x, float y, float z);
        void setCastShadow(bool v);
        void updateShadows(Light *l);
        void drawShadow();

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


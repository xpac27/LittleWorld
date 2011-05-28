#ifndef DEF_WORLD
#define DEF_WORLD

#include "Camera.h"
#include "Object.h"
#include "ObjectComparer.h"
#include "object/DynamicObject.h"
#include "object/StaticObject.h"
#include "util/Pathfinder.h"
#include "util/Conf.h"

#include <list>
#include <iostream>

class World
{
    public:

        World();

        void draw();
        void update(float time);
        void addDynamicObject(DynamicObject *o);
        void addStaticObject(StaticObject *o);
        void setMousePosition(unsigned int x, unsigned int y);
        void setFocus(Object *o);
        void updateMousePosition(float mouseScreenX, float mouseScreenY);
        void dispatch(unsigned const int type);

        static unsigned const int ON_MOUSE_LEFT_DOWN;

        float mouseX;
        float mouseY;


    private:

        std::list<DynamicObject*> dynamicObjectList;
        std::list<StaticObject*>  staticObjectList;

        Camera camera;
        Pathfinder pathfinder;
};

#endif


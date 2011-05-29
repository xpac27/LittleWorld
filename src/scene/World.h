#ifndef DEF_WORLD
#define DEF_WORLD

#include "Camera.h"
#include "Light.h"
#include "Object.h"
#include "ObjectComparer.h"
#include "object/DynamicObject.h"
#include "object/StaticObject.h"
#include "../ai/Pathfinder.h"
#include "../resources/Conf.h"

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
        void addLight(Light *o);
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
        std::list<Light*>         lightList;

        Camera camera;
        Pathfinder pathfinder;
};

#endif


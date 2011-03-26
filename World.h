#ifndef DEF_WORLD
#define DEF_WORLD

#include "Camera.h"
#include "object/DynamicObject.h"
#include "object/StaticObject.h"
#include "util/Position.h"
#include "util/Pathfinder.h"
#include "util/Conf.h"

#include <boost/signal.hpp>
#include <list>
#include <iostream>


class World
{
    public:

        World();

        boost::signal<void ()> ON_MOUSE_LEFT_DOWN;

        void draw();
        void update(float time);
        void addDynamicObject(DynamicObject *o);
        void addStaticObject(StaticObject *o);
        void setMousePosition(unsigned int x, unsigned int y);
        void setFocus(Object *o);
        void updateMousePosition(float mouseScreenX, float mouseScreenY);

        float mouseX;
        float mouseY;


    private:

        std::list<DynamicObject*> dynamicObjectList;
        std::list<StaticObject*>  staticObjectList;

        Camera camera;
        Pathfinder pathfinder;
};

#endif


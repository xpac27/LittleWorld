#ifndef DEF_WORLD
#define DEF_WORLD

#include "Camera.h"
#include "object/DynamicObject.h"
#include "object/StaticObject.h"
#include "util/Position.h"

#include <boost/signal.hpp>
#include <list>
#include <vector>
#include <map>
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

        std::vector<StaticObject*> getTraversingStaticObjects(Position *from, Position *to);

        int mouseX;
        int mouseY;


    private:

        std::list<DynamicObject*> dynamicObjectList;
        std::list<StaticObject*>  staticObjectList;

        std::map<int, std::map<int, std::vector<StaticObject*> > >staticObjectMap;

        Camera  camera;
};

#endif


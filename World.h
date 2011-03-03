#ifndef DEF_WORLD
#define DEF_WORLD

#include "object/DynamicObject.h"

#include <boost/signal.hpp>
#include <list>

class World
{
    public:

        World();

        boost::signal<void ()> ON_MOUSE_LEFT_DOWN;

        void draw();
        void update(float time);
        void addDynamicObject(DynamicObject *o);


    private:

        std::list<DynamicObject*> dynamicObjectList;
};

#endif


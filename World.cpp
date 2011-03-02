#include "World.h"

using namespace std;

World::World()
{
}

void World::draw()
{
    list<DynamicObject*>::iterator i;
    for (i = dynamicObjectList.begin(); i != dynamicObjectList.end(); ++ i)
    {
        (*i)->draw();
    }
}

void World::update(float time)
{
    list<DynamicObject*>::iterator i;
    for (i = dynamicObjectList.begin(); i != dynamicObjectList.end(); ++ i)
    {
        (*i)->update(time);
    }
}

void World::addDynamicObject(DynamicObject *o)
{
    o->init();
    dynamicObjectList.push_back(o);
}


#include "World.h"

World::World()
{
}

void World::draw()
{
    std::list<DynamicObject*>::iterator i;
    for (i = this->dynamicObjectList.begin(); i != this->dynamicObjectList.end(); ++ i)
    {
        (*i)->draw();
    }
}

void World::update(float time)
{
    std::list<DynamicObject*>::iterator i;
    for (i = this->dynamicObjectList.begin(); i != this->dynamicObjectList.end(); ++ i)
    {
        (*i)->update(time);
    }
}

void World::addDynamicObject(DynamicObject *o)
{
    o->init();
    this->dynamicObjectList.push_back(o);
}


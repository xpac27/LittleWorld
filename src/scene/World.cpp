#include "World.h"

using namespace std;

unsigned const int World::ON_MOUSE_LEFT_DOWN = 1;
unsigned const int World::ON_WINDOW_RESIZED  = 2;

World::World()
{
}

void World::draw()
{
    list<Object*> objectList;
    for (list<StaticObject*>::iterator i = staticObjectList.begin(); i != staticObjectList.end(); ++ i)
    {
        objectList.push_back(*i);
    }
    for (list<DynamicObject*>::iterator i = dynamicObjectList.begin(); i != dynamicObjectList.end(); ++ i)
    {
        objectList.push_back(*i);
    }
    camera.draw(&objectList, &lightList);
}

void World::update(float time)
{
    for (list<DynamicObject*>::iterator i = dynamicObjectList.begin(); i != dynamicObjectList.end(); ++ i)
    {
        (*i)->update(time);
    }

    camera.update(time);
}

void World::addDynamicObject(DynamicObject *o)
{
    o->init(&pathfinder);
    dynamicObjectList.push_back(o);
}

void World::addStaticObject(StaticObject *o)
{
    o->init();
    staticObjectList.push_back(o);
    pathfinder.addStaticObject(o);
}

void World::addLight(Light *o)
{
    lightList.push_back(o);
}

void World::setFocus(Object *o)
{
    camera.setFocus(o);
}

void World::updateMousePosition(float mouseScreenX, float mouseScreenY)
{
    // Apply transformation
    mouseY = (mouseScreenY * 2.f - mouseScreenX) / 2.f;
    mouseX = mouseScreenX + mouseY;

    // Scale
    mouseY *= 2.f;
    mouseX *= 2.f;

    // Add camera offset
    mouseX += camera.getX();
    mouseY += camera.getZ();
}

void World::dispatch(unsigned const int type)
{
    for (list<DynamicObject*>::iterator i = dynamicObjectList.begin(); i != dynamicObjectList.end(); ++ i)
    {
        (*i)->onNotify(type);
    }
}


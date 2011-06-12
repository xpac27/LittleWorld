#include "World.h"

using namespace std;

unsigned const int World::ON_MOUSE_LEFT_DOWN = 1;

World::World()
{
}

void World::draw()
{
    list<Object*> objectList;
    for (list<StaticObject*>::iterator Si = staticObjectList.begin(); Si != staticObjectList.end(); ++ Si)
    {
        objectList.push_back(*Si);
    }
    for (list<DynamicObject*>::iterator Di = dynamicObjectList.begin(); Di != dynamicObjectList.end(); ++ Di)
    {
        objectList.push_back(*Di);
    }
    // Looks light this is not useful
    //objectList.sort(ObjectComparer());

    camera.draw(&objectList, &lightList);
}

void World::update(float time)
{
    list<DynamicObject*>::iterator i;
    for (i = dynamicObjectList.begin(); i != dynamicObjectList.end(); ++ i)
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
    for (list<DynamicObject*>::iterator Di = dynamicObjectList.begin(); Di != dynamicObjectList.end(); ++ Di)
    {
        (*Di)->onNotify(type);
    }
}


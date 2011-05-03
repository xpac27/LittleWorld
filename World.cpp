#include "World.h"

using namespace std;

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
    objectList.sort();

    camera.draw(objectList);
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

void World::setFocus(Object *o)
{
    camera.setFocus(o);
}

void World::updateMousePosition(float mouseScreenX, float mouseScreenY)
{
    // Origin is on the screen so correct position
    mouseScreenX -= Conf::SCREEN_WIDTH / 2.f;
    mouseScreenY -= Conf::SCREEN_HEIGHT / 2.f;

    // Apply transformation
    mouseX = (mouseScreenX + (mouseScreenY * 2.f)) / 2.f;
    mouseY = ((mouseScreenY * 2.f) - mouseScreenX) / 2.f;

    // Add camera offset
    mouseX += camera.getX();
    mouseY += camera.getY();

    // Corect cursor
    mouseX += 16.f;
    mouseY += 8.f;
}


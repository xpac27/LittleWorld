#include "World.h"

using namespace std;

unsigned const int World::ON_MOUSE_LEFT_DOWN = 1;
unsigned const int World::ON_WINDOW_RESIZED  = 2;

World::World()
{
}

void World::draw()
{
    camera.draw(&meshList, &spriteList, &lightList);
}

void World::update(float time)
{
    for (list<Dynamic*>::iterator i = dynamicList.begin(); i != dynamicList.end(); ++ i)
    {
        (*i)->update(time);
    }

    camera.update(time);
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
    for (list<Dynamic*>::iterator i = dynamicList.begin(); i != dynamicList.end(); ++ i)
    {
        (*i)->onNotify(type);
    }
}

void World::addPlayer(bool focus)
{
}

void World::addEnemy(float x, float y)
{
}

void World::addWallTile(float x, float y, float h)
{
}

void World::addFloorTile(float x, float y)
{
}

void World::addLight(float x, float y, float z, float r, float v, float b)
{
}


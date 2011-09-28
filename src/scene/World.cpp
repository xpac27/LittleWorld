#include "World.h"

using namespace std;

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
    dynamicList.push_back(new Player(this, 512.f, 512.f, 64.f));
    meshList.push_back(new Mesh(dynamicList.back(), 64.f, 64.f, 1.f, 1.f, 0.f, 1.f));

    if (focus) camera.setFocus(dynamicList.back());
}

void World::addEnemy(float x, float z)
{
    dynamicList.push_back(new Enemy(this, x, z, 32.f));
    meshList.push_back(new Mesh(dynamicList.back(), 32.f, 32.f, 1.f, 0.f, 0.f, 1.f));
}

void World::addWallDecor(float x, float z, float h)
{
    staticList.push_back(new Decor(x, z, 128.f, false));
    meshList.push_back(new Mesh(staticList.back(), 128.f, h, 0.4f, 0.4f, 0.4f, 1.f));
    pathfinder.registerEntity(staticList.back());
}

void World::addFloorDecor(float x, float z)
{
    staticList.push_back(new Decor(x, z, 128.f, true));
    spriteList.push_back(new Sprite(staticList.back(), 128.f, 0.f, 0.9f, 0.9f, 0.9f, 1.f));
}

void World::addLight(float x, float y, float z, float r, float g, float b)
{
    staticList.push_back(new Emitter(x, y, z));
    lightList.push_back(new Light(staticList.back(), r, g, b));
}

float World::getMouseX() { return mouseX; }
float World::getMouseY() { return mouseY; }

vector<Vector3*> World::getPath(Vector3 *position, float toX, float toY, float s)
{
    return pathfinder.getPath(position->x, position->z, toX, toY, s);
}


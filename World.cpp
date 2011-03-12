#include "World.h"

using namespace std;

World::World()
{
}

void World::draw()
{
    list<StaticObject*>::iterator Si;
    for (Si = staticObjectList.begin(); Si != staticObjectList.end(); ++ Si)
    {
        camera.draw(*Si);
    }

    list<DynamicObject*>::iterator Di;
    for (Di = dynamicObjectList.begin(); Di != dynamicObjectList.end(); ++ Di)
    {
        camera.draw(*Di);
    }
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
    o->init();
    dynamicObjectList.push_back(o);
}

void World::addStaticObject(StaticObject *o)
{
    o->init();
    staticObjectList.push_back(o);
    staticObjectMap[o->getGridX()][o->getGridY()].push_back(o);
}

void World::setFocus(Object *o)
{
    camera.setFocus(o);
}

void World::updateMousePosition(float mouseScreenX, float mouseScreenY)
{
    // Origin is on the screen so correct position
    mouseScreenX -= 400.f;
    mouseScreenY -= 300.f;

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

vector<StaticObject*> World::getTraversingStaticObjects(Position *from, Position *to)
{
    vector<StaticObject*> objects;

    //Calculate m and b for the line equation:
    float m = ((to->y / 64.f) - (from->y / 64.f)) / ((to->x / 64.f) - (from->x / 64.f));
    float b = ((from->y + 32.f) / 64.f) - (m * ((from->x + 32.f) / 64.f));

    // Define vars (c=current, n=next, d=direction, e=end)
    float cx = (float)from->getGridX();
    float cy = (float)from->getGridY();
    float ex = (float)to->getGridX();
    float ey = (float)to->getGridY();
    float dx = (cx < ex) ? 1.f : -1.f;
    float dy = (cy < ey) ? 1.f : -1.f;
    float nx, ny;

    unsigned int i = 0;
    unsigned int n = 0;

    for (i = 0; i < staticObjectMap[cx][cy].size(); i ++)
    {
        objects.push_back(staticObjectMap[cx][cy][i]);
    }

    // While we do not reach the end position
    while ((cx != ex || cy != ey) && n < 60)
    {
        // Move 1 tile on x and on y
        nx = cx + dx;
        ny = cy + dy;

        // Find x for the next y value and compare it to the current tile x value
        if (floor((dy == 1) ? ((ny - b) / m) : ((cy - b) / m)) == cx)
        {
            cy = ny;
        }
        else
        {
            cx = nx;
        }
        n ++;

        // Add all the objects in this tile to the list
        for (i = 0; i < staticObjectMap[cx][cy].size(); i ++)
        {
            objects.push_back(staticObjectMap[cx][cy][i]);
        }
    }
    return objects;
}


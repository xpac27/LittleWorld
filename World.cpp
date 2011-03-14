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

    float s  = dynamicObjectList.back()->getSize();
    float x1 = dynamicObjectList.back()->getX();
    float y1 = dynamicObjectList.back()->getY();
    float x2 = mouseX;
    float y2 = mouseY;

    s /= 4.f;

    int const dx = (x1 < x2) ? 1 : -1;
    int const dy = (y1 < y2) ? 1 : -1;

    Position p1, p2, p3, p4, p5, p6;

    p5.set(x1, y1);
    p6.set(x2, y2);

    p1.set(x1 + (s * dx), y1 - (s * dy));
    p2.set(x2 + (s * dx), y2 - (s * dy));
    p3.set(x1 - (s * dx), y1 + (s * dy));
    p4.set(x2 - (s * dx), y2 + (s * dy));

    camera.toScreenPosition(&p1);
    camera.toScreenPosition(&p2);
    camera.toScreenPosition(&p3);
    camera.toScreenPosition(&p4);
    camera.toScreenPosition(&p5);
    camera.toScreenPosition(&p6);

    glColor4f(1.0f, 0.0f, 0.0f, 1.f);

    glBegin(GL_LINES);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(p3.x, p3.y);
        glVertex2f(p4.x, p4.y);
    glEnd();

    glColor4f(0.0f, 1.0f, 0.0f, 1.f);

    glBegin(GL_LINES);
        glVertex2f(p5.x, p5.y);
        glVertex2f(p6.x, p6.y);
    glEnd();
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

    pathfinder.addStaticObject(o);
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

std::vector<Position*> World::getPath(float x1, float y1, float x2, float y2, float s)
{
    return pathfinder.getPath(x1, y1, x2, y2, s);
}


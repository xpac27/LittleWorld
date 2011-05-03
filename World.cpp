#include "World.h"

using namespace std;

World::World()
{
}

void World::draw()
{
    list<StaticObject*>::iterator Si;
    list<DynamicObject*>::iterator Di;

    for (Si = staticObjectList.begin(); Si != staticObjectList.end(); ++ Si)
    {
        camera.draw(*Si);
    }

    for (Di = dynamicObjectList.begin(); Di != dynamicObjectList.end(); ++ Di)
    {
        camera.draw(*Di);
    }

    //glColorMask(0, 0, 0, 0);
    //glDisable(GL_DEPTH_TEST);
    //glEnable(GL_STENCIL_TEST);

    //glStencilFunc(GL_ALWAYS, 1, 1);
    //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    //for (Si = staticObjectList.begin(); Si != staticObjectList.end(); ++ Si)
    //{
        //camera.drawShadow(*Si);
    //}
    //for (Di = dynamicObjectList.begin(); Di != dynamicObjectList.end(); ++ Di)
    //{
        //camera.drawShadow(*Di);
    //}

    //glStencilFunc(GL_EQUAL, 1, 1);
    //glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

    //glColorMask(1, 1, 1, 1);
    //glEnable(GL_DEPTH_TEST);
    //glStencilFunc(GL_EQUAL, 1, 1);
    //glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    //glColor4f(0.0f, 0.0f, 0.0f, 0.5f);

    //glBegin(GL_QUADS);
        //glVertex2f(0.f, 0.f);
        //glVertex2f(Conf::SCREEN_WIDTH, 0.f);
        //glVertex2f(Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT);
        //glVertex2f(0.f, Conf::SCREEN_HEIGHT);
    //glEnd();

    //glDisable(GL_STENCIL_TEST);
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


#include "World.h"

using namespace std;

World::World()
{
}

void World::draw()
{
    //static GLfloat  LightAmb[] = {0.0f, 0.0f, 0.0f, 0.0f};              // Ambient Light
    //static GLfloat  LightDif[] = {1.0f, 1.0f, 1.0f, 1.0f};              // Diffuse Light
    //static GLfloat  LightPos[] = {Conf::SCREEN_WIDTH / 2.0f, Conf::SCREEN_HEIGHT / 2.0f, 30.0f, 1.0f};         // Light Position

    //glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);     // Set The Ambient Lighting For Light0
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);     // Set The Diffuse Lighting For Light0
    //glLightfv(GL_LIGHT0, GL_POSITION, LightPos);    // Set The Position For Light0

    //glEnable(GL_LIGHT0);                            // Enable Light 0
    //glEnable(GL_LIGHTING);                          // Enable Lighting

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

    glColorMask(0, 0, 0, 0);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);

    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    for (Si = staticObjectList.begin(); Si != staticObjectList.end(); ++ Si)
    {
        camera.drawShadow(*Si);
    }
    for (Di = dynamicObjectList.begin(); Di != dynamicObjectList.end(); ++ Di)
    {
        camera.drawShadow(*Di);
    }

    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    for (Si = staticObjectList.begin(); Si != staticObjectList.end(); ++ Si)
    {
        camera.drawShadowSides(*Si);
    }
    for (Di = dynamicObjectList.begin(); Di != dynamicObjectList.end(); ++ Di)
    {
        camera.drawShadowSides(*Di);
    }

    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

    for (Si = staticObjectList.begin(); Si != staticObjectList.end(); ++ Si)
    {
        if ((*Si)->getHeight() != 0)
        {
            camera.drawShadowExclusions(*Si);
        }
    }
    for (Di = dynamicObjectList.begin(); Di != dynamicObjectList.end(); ++ Di)
    {
        if ((*Di)->getHeight() != 0)
        {
            camera.drawShadowExclusions(*Di);
        }
    }

    glColorMask(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);

    glBegin(GL_QUADS);
        glVertex2f(0.f, 0.f);
        glVertex2f(Conf::SCREEN_WIDTH, 0.f);
        glVertex2f(Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT);
        glVertex2f(0.f, Conf::SCREEN_HEIGHT);
    glEnd();

    glDisable(GL_STENCIL_TEST);


    //glDisable(GL_DEPTH_TEST);
    //glColorMask(0, 0, 0, 0);
    //glEnable(GL_STENCIL_TEST);
    //glStencilFunc(GL_ALWAYS, 1, 1);                 // Always Passes, 1 Bit Plane, 1 As Mask
    //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);      // We Set The Stencil Buffer To 1 Where We Draw Any Polygon
                                                    //// Keep If Test Fails, Keep If Test Passes But Buffer Test Fails
                                                    //// Replace If Test Passes
    //glBegin(GL_QUADS);
        //glVertex2f(20.f, 20.f);
        //glVertex2f(100.f, 20.f);
        //glVertex2f(100.f, 100.f);
        //glVertex2f(20.f, 100.f);
    //glEnd();

    //glEnable(GL_DEPTH_TEST);                        // Enable Depth Testing
    //glColorMask(1, 1, 1, 1);                        // Set Color Mask to TRUE, TRUE, TRUE, TRUE
    //glStencilFunc(GL_EQUAL, 1, 1);                  // We Draw Only Where The Stencil Is 1
                                                    //// (I.E. Where The Floor Was Drawn)
    //glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);         // Don't Change The Stencil Buffer

    //glColor4f(0.0f, 0.0f, 0.0f, 0.5f);

    //glBegin(GL_QUADS);
        //glVertex2f(0.f, 0.f);
        //glVertex2f(Conf::SCREEN_WIDTH, 0.f);
        //glVertex2f(Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT);
        //glVertex2f(0.f, Conf::SCREEN_HEIGHT);
    //glEnd();

    //glDisable(GL_STENCIL_TEST);                     // We Don't Need The Stencil Buffer Any More (Disable)

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


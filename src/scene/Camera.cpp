#include "Camera.h"

using namespace std;

Camera::Camera()
{
    speed     = 50.f;
    tolerance = 50.f;
    inertia   = 0.3f;

    position.x = 0.f;
    position.y = 0.f;
    position.z = 0.f;
}

void Camera::draw(std::list<Object*> *objects, std::list<Light*> *lights)
{
    // When rendered use addition for colour.
    glBlendFunc(GL_ONE, GL_ONE);

    // Use a black ambient color
    GLfloat ambientColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    // Clear the color mask
    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT);

    // Translate to camera's position
    glPushMatrix();
    glTranslatef(position.x * -1.f,  position.y * -1.f, position.z * -1.f);

    // Render the entire scene to the depth buffer (no textures, only ambient lights)
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClear(GL_DEPTH_BUFFER_BIT);

    // Disable writing to the color mask
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);

    for (list<Object*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        glPushMatrix();
        glTranslatef((*o)->getX(), (*o)->getY(), (*o)->getZ());

        (*o)->draw();

        glPopMatrix();
    }

    // Disable writting on depth mask
    glDepthMask(GL_FALSE);

    // Activate stencil buffer
    //glEnable(GL_STENCIL_TEST);

    // For each light in the scene
    for (list<Light*>::iterator l = lights->begin(); l != lights->end(); ++ l)
    {
        // generate shadow volumes
        //for (list<Object*>::iterator o = objects->begin(); o != objects->end(); ++ o)
        //{
            //if ((*o)->shadowEnabled() && (*o)->getHeight() > 0.f)
            //{
                //(*o)->updateShadows(*l);
            //}
        //}

        // clear the stencil buffer
        //glClear(GL_STENCIL_BUFFER_BIT);

        // Render shadow volumes to stencil buffer
        //glStencilFunc(GL_ALWAYS, GL_ONE, GL_ONE);
        //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        //for (list<Object*>::iterator o = objects->begin(); o != objects->end(); ++ o)
        //{
            //if ((*o)->shadowEnabled() && (*o)->getHeight() > 0.f)
            //{
                //glPushMatrix();
                //translateObject(*o);

                //(*o)->drawShadow();

                //glPopMatrix();
            //}
        //}

        // Activate the current light only
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_BLEND);
        glEnable(GL_COLOR_MATERIAL);

        // Only render where stencil is not egual to one
        //glStencilFunc(GL_NOTEQUAL, GL_ONE, GL_ONE);
        //glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

        // Enable writing on the color mask
        glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);

        // Place the light to the right position
        glPushMatrix();
        glTranslatef((*l)->getX(), (*l)->getY(), (*l)->getZ());

        (*l)->setup();

        glPopMatrix();

        // Render the entire scene
        for (list<Object*>::iterator o = objects->begin(); o != objects->end(); ++ o)
        {
            glPushMatrix();
            glTranslatef((*o)->getX(), (*o)->getY(), (*o)->getZ());

            (*o)->draw();

            glPopMatrix();
        }

        // Deactive the current light
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_BLEND);
        glDisable(GL_COLOR_MATERIAL);

        // Disable writing to the color mask
        glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    }

    // Deactivate stencil buffer
    glDisable(GL_STENCIL_TEST);

    // Enable writing on the color mask
    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (list<Object*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        glPushMatrix();
        glTranslatef((*o)->getX(), (*o)->getY(), (*o)->getZ());

        (*o)->drawOutline();

        glPopMatrix();
    }

    // Disable writing to the color mask
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    glDisable(GL_BLEND);

    glPopMatrix();
}

void Camera::update(float time)
{
    if (position.x - focus->getX() > tolerance)
    {
        position.x -= (position.x - (focus->getX() + tolerance)) / (inertia / time);
    }
    else if (focus->getX() - position.x > tolerance)
    {
        position.x += ((focus->getX() - tolerance) - position.x) / (inertia / time);
    }

    if (position.y - focus->getY() > tolerance)
    {
        position.y -= (position.y - (focus->getY() + tolerance)) / (inertia / time);
    }
    else if (focus->getY() - position.y > tolerance)
    {
        position.y += ((focus->getY() - tolerance) - position.y) / (inertia / time);
    }

    if (position.z - focus->getZ() > tolerance)
    {
        position.z -= (position.z - (focus->getZ() + tolerance)) / (inertia / time);
    }
    else if (focus->getZ() - position.z > tolerance)
    {
        position.z += ((focus->getZ() - tolerance) - position.z) / (inertia / time);
    }
}

void Camera::setFocus(Object *o)
{
    focus = o;
}

float Camera::getX()
{
    return position.x;
}

float Camera::getY()
{
    return position.y;
}

float Camera::getZ()
{
    return position.z;
}


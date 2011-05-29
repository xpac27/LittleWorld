#include "Camera.h"

using namespace std;

Camera::Camera()
{
    speed     = 50.f;
    tolerance = 50.f;
    inertia   = 0.3f;

    position.x = 0.f;
    position.y = 0.f;
}

void Camera::draw(std::list<Object*> objects, std::list<Light*> lights)
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
    translateCamera();

    // Render the entire scene to the depth buffer (no textures, only ambient lights)
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClear(GL_DEPTH_BUFFER_BIT);

    // Disable writing to the color mask
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);

    for (list<Object*>::iterator o = objects.begin(); o != objects.end(); ++ o)
    {
        glPushMatrix();
        translateObject(*o);

        (*o)->draw();

        glPopMatrix();
    }

    // Disable writting on depth mask
    glDepthMask(GL_FALSE);

    // Activate stencil buffer
    glEnable(GL_STENCIL_TEST);

    // For each light in the scene
    for (list<Light*>::iterator l = lights.begin(); l != lights.end(); ++ l)
    {
        // generate shadow volumes
        for (list<Object*>::iterator o = objects.begin(); o != objects.end(); ++ o)
        {
            if ((*o)->shadowEnabled() && (*o)->getHeight() > 0.f)
            {
                (*o)->updateShadows(*l);
            }
        }

        // clear the stencil buffer
        glClear(GL_STENCIL_BUFFER_BIT);

        // Render shadow volumes to stencil buffer
        glStencilFunc(GL_ALWAYS, GL_ONE, GL_ONE);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        for (list<Object*>::iterator o = objects.begin(); o != objects.end(); ++ o)
        {
            if ((*o)->shadowEnabled() && (*o)->getHeight() > 0.f)
            {
                glPushMatrix();
                translateObject(*o);

                (*o)->drawShadow();

                glPopMatrix();
            }
        }

        for (list<Object*>::iterator o = objects.begin(); o != objects.end(); ++ o)
        {
            if ((*o)->shadowEnabled() && (*o)->getHeight() > 0.f)
            {
                glPushMatrix();
                translateObject(*o);

                // Clear object volume from the stencil buffer
                glStencilFunc(GL_EQUAL, GL_ONE, GL_ONE);
                glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

                (*o)->draw();

                // Render shadow volumes to stencil buffer
                glStencilFunc(GL_ALWAYS, GL_ONE, GL_ONE);
                glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

                (*o)->drawWallShadows(objects);

                glPopMatrix();
            }
        }

        // Activate the current light only
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_BLEND);
        glEnable(GL_COLOR_MATERIAL);

        // Only render where stencil egual zero
        glStencilFunc(GL_EQUAL, GL_ZERO, GL_ONE);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

        // Enable writing on the color mask
        glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);

        // Place the light to the right position
        glPushMatrix();
        translateLight(*l);

        (*l)->setup();

        glPopMatrix();

        // Render the entire scene
        for (list<Object*>::iterator o = objects.begin(); o != objects.end(); ++ o)
        {
            glPushMatrix();
            translateObject(*o);

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
}

void Camera::toScreenPosition(Vector2 *p)
{
    float nx = p->x;
    float ny = p->y;
    p->x = nx - ny;
    p->y = (nx + ny) / 2.f;
    p->x += position.y - position.x + 288.f + (Conf::SCREEN_WIDTH / 2.f) - (Conf::SCREEN_HEIGHT / 2.f);
    p->y += ((position.x + position.y - (Conf::SCREEN_WIDTH / 2.f) - (Conf::SCREEN_HEIGHT / 2.f)) / -2.f) - 64.f;
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

void Camera::translateCamera()
{
    glTranslatef
    (
        position.y - position.x + 288.f + (Conf::SCREEN_WIDTH / 2.f) - (Conf::SCREEN_HEIGHT / 2.f), // Origin is centered on the screen
        ((position.x + position.y - (Conf::SCREEN_WIDTH / 2.f) - (Conf::SCREEN_HEIGHT / 2.f)) / -2.f) - 64.f, // So minus alf screen width and height
        0.f
    );
}

void Camera::translateObject(Object *o)
{
    translate(o->getX(), o->getY(), o->getHeight(), o->getIndex());
}

void Camera::translateLight(Light *l)
{
    translate(l->getX(), l->getY(), 0.f, 0.f);
}

void Camera::translate(float x, float y, float h, float i)
{
    // Z index is calc using screen's Y coord lowered to tiles screen height + object's index
    glTranslatef(x - y, (x + y) / 2.f, (h == 0.f) ? -1.f : -1.f / (((x + y) / 2.f) / 64.f + i));
}


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
    // Translate to camera's position
    glPushMatrix();
    glTranslatef(position.x * -1.f,  position.y * -1.f, position.z * -1.f);

    // Use a black ambient color
    GLfloat ambientColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);


    // STEP 0: setup
    // =============

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);

    glClear(GL_COLOR_BUFFER_BIT);

    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);


    // STEP 1: render depth
    // ====================

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glClear(GL_DEPTH_BUFFER_BIT);

    glFrontFace(GL_CW);
    drawAll(objects);

    glDepthMask(GL_FALSE);


    // STEP 2: loop through lights
    // ===========================

    glEnable(GL_STENCIL_TEST);

    for (list<Light*>::iterator l = lights->begin(); l != lights->end(); ++ l)
    {
        // STEP 3: render shadow volumes
        // =============================

        glClear(GL_STENCIL_BUFFER_BIT);

        glDepthFunc(GL_LESS);
        glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFFL);

        updateAllShadows(objects, *l);

        #ifdef GL_EXT_stencil_two_side && GL_EXT_stencil_wrap

        glEnable(GL_STENCIL_TEST_TWO_SIDE_EXT);

        glActiveStencilFaceEXT(GL_BACK);
        glStencilOp(GL_KEEP, GL_KEEP, GL_INCR_WRAP_EXT);

        glActiveStencilFaceEXT(GL_FRONT);
        glStencilOp(GL_KEEP, GL_KEEP, GL_DECR_WRAP_EXT);

        drawAllShadows(objects, *l);

        glDisable(GL_STENCIL_TEST_TWO_SIDE_EXT);

        #else

        glFrontFace(GL_CW);
        glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
        drawAllShadows(objects, *l);

        glFrontFace(GL_CCW);
        glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
        drawAllShadows(objects, *l);

        #endif


        // STEP 4: render the scene
        // ========================

        glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_BLEND);
        glEnable(GL_COLOR_MATERIAL); // TODO avoid

        setupLight(*l);

        glStencilFunc(GL_EQUAL, 0, 0xFFFFFFFFL);
        glBlendFunc(GL_ONE, GL_ONE);
        glDepthFunc(GL_LEQUAL);

        glFrontFace(GL_CW);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        drawAll(objects);

        glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_BLEND);
        glDisable(GL_COLOR_MATERIAL);
    }

    glDisable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);


    // STEP 4: wireframe
    // =================

    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    outlineAll(objects);

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
    position.x = o->getX();
    position.z = o->getZ();
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

void Camera::drawAll(std::list<Object*> *objects)
{
    for (list<Object*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        glPushMatrix();
        translateObject(*o);
        (*o)->draw();
        glPopMatrix();
    }
}

void Camera::outlineAll(std::list<Object*> *objects)
{
    for (list<Object*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        glPushMatrix();
        glTranslatef((*o)->getX(), (*o)->getY(), (*o)->getZ());

        (*o)->drawOutline();

        glPopMatrix();
    }
}

void Camera::drawAllShadows(std::list<Object*> *objects, Light *l)
{
    for (list<Object*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        if ((*o)->shadowEnabled() && (*o)->getHeight() > 0.f)
        {
            glPushMatrix();
            translateObject(*o);
            (*o)->drawShadow(l);
            glPopMatrix();
        }
    }
}

void Camera::updateAllShadows(std::list<Object*> *objects, Light *l)
{
    for (list<Object*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        if ((*o)->shadowEnabled() && (*o)->getHeight() > 0.f)
        {
            (*o)->updateShadows(l);
        }
    }
}

void Camera::translateObject(Object *o)
{
    glTranslatef(o->getX(), o->getY(), o->getZ());
}

void Camera::setupLight(Light *l)
{
    glPushMatrix();
    glTranslatef(l->getX(), l->getY(), l->getZ());
    l->setup();
    glPopMatrix();
}


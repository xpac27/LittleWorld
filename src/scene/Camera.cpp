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

void Camera::draw(std::list<Mesh*> *meshes, std::list<Sprite*> *sprites, std::list<Light*> *lights)
{
    // Translate to camera's position
    glPushMatrix();
    glTranslatef(position.x * -1.f,  position.y * -1.f, position.z * -1.f);

    updateViewFrustum();

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
    drawAllMeshes(meshes);
    drawAllSprites(sprites);

    glDepthMask(GL_FALSE);


    // STEP 2: loop through lights
    // ===========================

    glEnable(GL_STENCIL_TEST);

    for (list<Light*>::iterator l = lights->begin(); l != lights->end(); ++ l)
    {
        // TODO perfome culling on shadow volumes against view frustum
        // TODO extrude shadow volume by the size of the light's radius
        // http://http.developer.nvidia.com/GPUGems/gpugems_ch09.html SEC-9.5

        // Skeep this light if it's too far
        //if ((*l)->getIntensityAtPosition(position) < 0.004f) continue;

        // STEP 3: render shadow volumes
        // =============================

        // TODO skeep this object if it's not lit
        //l->getIntensityAtPosition((*o)->getPosition()) > 0.004f

        glClear(GL_STENCIL_BUFFER_BIT);

        glDepthFunc(GL_LESS);
        glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFFL);

        #ifdef GL_EXT_stencil_two_side && GL_EXT_stencil_wrap

        glEnable(GL_STENCIL_TEST_TWO_SIDE_EXT);

        glActiveStencilFaceEXT(GL_BACK);
        glStencilOp(GL_KEEP, GL_KEEP, GL_INCR_WRAP_EXT);

        glActiveStencilFaceEXT(GL_FRONT);
        glStencilOp(GL_KEEP, GL_KEEP, GL_DECR_WRAP_EXT);

        drawAllShadows(meshes, *l);

        glDisable(GL_STENCIL_TEST_TWO_SIDE_EXT);

        #else

        glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_INCR);
        glStencilOpSeparate(GL_BACK, GL_KEEP, GL_KEEP, GL_DECR);
        drawAllShadows(meshes, *l);

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
        drawAllMeshes(meshes);
        drawAllSprites(sprites);

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

    //glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    //glEnable(GL_BLEND);

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //outlineAllMeshes(meshes);
    //outlineAllSprites(sprites);
    //outlineAllLights(lights);

    //glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    //glDisable(GL_BLEND);

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

void Camera::updateViewFrustum()
{
    Matrix4x4f projMatrix;
    Matrix4x4f viewMatrix;

    glGetFloatv(GL_PROJECTION_MATRIX, projMatrix.m);
    glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix.m);

    viewFrustum.update(projMatrix * viewMatrix);
}

void Camera::setFocus(Entity *e)
{
    focus = e;
    position.x = e->getX();
    position.z = e->getZ();
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

void Camera::drawObject(Object *o)
{
    if (viewFrustum.sphereInFrustum(o->getPosition(), o->getSize()))
    {
        glPushMatrix();
        glTranslatef(o->getX(), o->getY(), o->getZ());
        o->draw();
        glPopMatrix();
    }
}

void Camera::outlineObject(Object *o)
{
    if (viewFrustum.sphereInFrustum(o->getPosition(), o->getSize()))
    {
        glPushMatrix();
        glTranslatef(o->getX(), o->getY(), o->getZ());
        o->outline();
        glPopMatrix();
    }
}

void Camera::drawAllMeshes(std::list<Mesh*> *objects)
{
    for (list<Mesh*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        drawObject(*o);
    }
}

void Camera::outlineAllMeshes(std::list<Mesh*> *objects)
{
    for (list<Mesh*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        outlineObject(*o);
    }
}

void Camera::drawAllSprites(std::list<Sprite*> *objects)
{
    for (list<Sprite*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        drawObject(*o);
    }
}

void Camera::outlineAllSprites(std::list<Sprite*> *objects)
{
    for (list<Sprite*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        outlineObject(*o);
    }
}

void Camera::drawAllLights(std::list<Light*> *objects)
{
    for (list<Light*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        outlineObject(*o);
    }
}

void Camera::outlineAllLights(std::list<Light*> *objects)
{
    for (list<Light*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        outlineObject(*o);
    }
}

void Camera::setupLight(Light *l)
{
    glPushMatrix();
    glTranslatef(l->getX(), l->getY(), l->getZ());
    l->setup();
    glPopMatrix();
}

void Camera::drawAllShadows(std::list<Mesh*> *objects, Light *l)
{
    for (list<Mesh*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
        glPushMatrix();
        glTranslatef((*o)->getX(), (*o)->getY(), (*o)->getZ());
        (*o)->drawShadow(l, false);
        glPopMatrix();
    }
}

//void Camera::updateObjectsVisibility(std::list<Object*> *objects)
//{
    //for (list<Object*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    //{
        //(*o)->setVisibility(viewFrustum.sphereInFrustum((*o)->getPosition(), (*o)->getSize()));
    //}
//}


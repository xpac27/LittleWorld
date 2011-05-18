#include "Object.h"

using namespace std;

Object::Object(World *W, float h, bool s) : world(W), height(h), shadow(s)
{
    index = height > 0.f ? 2.f : 1.f;

    edgeCastShadowBR = false;
    edgeCastShadowBL = false;
    edgeCastShadowTR = false;
    edgeCastShadowTL = false;

    position.set(0.f, 0.f, 0.f);
    setSize(32.f);
}

void Object::init()
{
}

void Object::setSize(float s)
{
    size = s;

    float alfSize = size / 2.f;
    float quarterSize = size / 4.f;

    faceL.set(-alfSize, 0.f, -alfSize, -height, 0.f, -height + quarterSize, 0.f, quarterSize);
    faceR.set(alfSize, 0.f, alfSize, -height, 0.f, -height + quarterSize, 0.f, quarterSize);
    faceT.set(0.f, -quarterSize, alfSize, 0.f, 0.f, quarterSize, -alfSize, 0.f);
}

void Object::setPosition(float x, float y)
{
    position.set(x, y);
}

void Object::draw()
{
    if (height == 0)
    {
        faceT.draw();
    }
    else
    {
        glPushMatrix();
        glTranslatef(0.f, -height, 0.f);
        faceT.draw();
        glPopMatrix();
        glColor4f(0.6f, 0.6f, 0.6f, 1.f);
        faceL.draw();
        faceR.draw();
    }
}

void Object::drawOutline()
{
    glColor4f(1.f, 1.f, 1.f, 0.6f);

    if (height == 0)
    {
        faceT.outline();
    }
    else
    {
        faceL.outline();
        faceR.outline();
        glPushMatrix();
        glTranslatef(0.f, -height, 0.f);
        faceT.outline();
        glPopMatrix();
    }
}

Quad Object::updateShadow(Quad *shadow, Segment *edge, float lx, float ly)
{
    float h = height / 64.f;

    shadow->set
    (
        edge->p1.x, edge->p1.y,
        edge->p1.x + (edge->p1.x - lx) * h, edge->p1.y + (edge->p1.y - ly) * h,
        edge->p2.x + (edge->p2.x - lx) * h, edge->p2.y + (edge->p2.y - ly) * h,
        edge->p2.x, edge->p2.y
    );
}

void Object::updateShadows(float lx, float ly)
{
    if (shadow && height > 0.f)
    {
        edgeCastShadowBR = shadow && edgeCastShadow(getBaseEdgeBR(), lx, ly);
        edgeCastShadowBL = shadow && edgeCastShadow(getBaseEdgeBL(), lx, ly);
        edgeCastShadowTR = shadow && edgeCastShadow(getBaseEdgeTR(), lx, ly);
        edgeCastShadowTL = shadow && edgeCastShadow(getBaseEdgeTL(), lx, ly);

        if (edgeCastShadowBR) updateShadow(&shadowBR, getBaseEdgeBR(), lx, ly);
        if (edgeCastShadowBL) updateShadow(&shadowBL, getBaseEdgeBL(), lx, ly);
        if (edgeCastShadowTR) updateShadow(&shadowTR, getBaseEdgeTR(), lx, ly);
        if (edgeCastShadowTL) updateShadow(&shadowTL, getBaseEdgeTL(), lx, ly);
    }
}

void Object::drawShadow()
{
    if (edgeCastShadowBR) shadowBR.draw();
    if (edgeCastShadowBL) shadowBL.draw();
    if (edgeCastShadowTR) shadowTR.draw();
    if (edgeCastShadowTL) shadowTL.draw();
}

void Object::drawWallShadows(list<Object*> objects)
{
    if (shadow && height > 0.f)
    {
        if (edgeCastShadowBL) faceL.draw();
        if (edgeCastShadowBR) faceR.draw();

        if (!edgeCastShadowBL || !edgeCastShadowBR)
        {
            // Translated objects shadows toward object's position
            Quad objectShadow;

            // Objects screen position
            Vector2 currentSP(getX() - getY(), (getX() + getY()) / 2.f);
            Vector2 translation;

            for (list<Object*>::iterator i = objects.begin(); i != objects.end(); ++ i)
            {
                if ((*i) != this && (*i)->shadowEnabled() && (*i)->getHeight() != 0.f)
                {
                    translation.x = ((*i)->getX() - (*i)->getY()) - currentSP.x;
                    translation.y = ((*i)->getX() + (*i)->getY()) / 2.f - currentSP.y;

                    // TODO We could try to avoid cloning shadow Quads

                    if ((*i)->edgeCastShadowTR)
                    {
                        objectShadow = (*(*i)->getShadowTR());
                        objectShadow.translate(translation);
                        drawWallShadow(&objectShadow, height < (*i)->getHeight() ? height : (*i)->getHeight());
                    }

                    if ((*i)->edgeCastShadowTL)
                    {
                        objectShadow = (*(*i)->getShadowTL());
                        objectShadow.translate(translation);
                        drawWallShadow(&objectShadow, height < (*i)->getHeight() ? height : (*i)->getHeight());
                    }

                    if ((*i)->edgeCastShadowBR)
                    {
                        objectShadow = (*(*i)->getShadowBR());
                        objectShadow.translate(translation);
                        drawWallShadow(&objectShadow, height < (*i)->getHeight() ? height : (*i)->getHeight());
                    }

                    if ((*i)->edgeCastShadowBL)
                    {
                        objectShadow = (*(*i)->getShadowBL());
                        objectShadow.translate(translation);
                        drawWallShadow(&objectShadow, height < (*i)->getHeight() ? height : (*i)->getHeight());
                    }
                }
            }
        }
    }
}

void Object::drawWallShadow(Quad *shadow, float h)
{
    vector<Vector2> pointList;

    bool c1 = !edgeCastShadowBL && shadow->containsPosition(&getBaseEdgeBL()->p2);
    bool c2 = (!edgeCastShadowBL || !edgeCastShadowBR) && shadow->containsPosition(&getBaseEdgeBL()->p1);
    bool c3 = !edgeCastShadowBR && shadow->containsPosition(&getBaseEdgeBR()->p1);

    if (c1) pointList.push_back(getBaseEdgeBL()->p2);

    if (!edgeCastShadowBL && (!c1 || !c2))
    {
        getBaseEdgeBL()->getIntesectionToSegment(&shadow->s1, &pointList);
        getBaseEdgeBL()->getIntesectionToSegment(&shadow->s2, &pointList);
        getBaseEdgeBL()->getIntesectionToSegment(&shadow->s3, &pointList);
    }

    if (c2) pointList.push_back(getBaseEdgeBL()->p1);

    if (!edgeCastShadowBR && (!c2 || !c3))
    {
        getBaseEdgeBR()->getIntesectionToSegment(&shadow->s1, &pointList);
        getBaseEdgeBR()->getIntesectionToSegment(&shadow->s2, &pointList);
        getBaseEdgeBR()->getIntesectionToSegment(&shadow->s3, &pointList);
    }

    if (c3) pointList.push_back(getBaseEdgeBR()->p1);

    if (pointList.size() > 1)
    {
        for (unsigned int i = 1; i < pointList.size(); i += 1)
        {
            glBegin(GL_QUADS);
                glVertex2f(pointList[i-1].x, pointList[i-1].y);
                glVertex2f(pointList[i-1].x, pointList[i-1].y - h);
                glVertex2f(pointList[i].x, pointList[i].y - h);
                glVertex2f(pointList[i].x, pointList[i].y);
            glEnd();
        }
    }
}

bool Object::edgeCastShadow(Segment *edge, float lx, float ly)
{
    // normal of 2nd point minus 1st point
    float nx = -1 * (edge->p2.y - edge->p1.y);
    float ny = edge->p2.x - edge->p1.x;

    // light minus 1st point
    lx = edge->p1.x - lx;
    ly = edge->p1.y - ly;

    // cross product
    if (nx * lx + ny * ly < 0.f)
    {
        return true;
    }
    return false;
}

float Object::getX()
{
    return position.x;
}

float Object::getY()
{
    return position.y;
}

float Object::getIndex()
{
    return index;
}

float Object::getHeight()
{
    return height;
}

float Object::getSize()
{
    return size;
}

bool Object::shadowEnabled()
{
    return shadow;
}

Segment* Object::getBaseEdgeBL()
{
    return &faceT.s3;
}

Segment* Object::getBaseEdgeBR()
{
    return &faceT.s2;
}

Segment* Object::getBaseEdgeTL()
{
    return &faceT.s4;
}

Segment* Object::getBaseEdgeTR()
{
    return &faceT.s1;
}

Quad* Object::getShadowBR()
{
    return &shadowBR;
}

Quad* Object::getShadowBL()
{
    return &shadowBL;
}

Quad* Object::getShadowTR()
{
    return &shadowTR;
}

Quad* Object::getShadowTL()
{
    return &shadowTL;
}



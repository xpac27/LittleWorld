#include "Object.h"

using namespace std;

Object::Object(World *W, float h, bool s) : world(W), height(h), shadow(s)
{
    index = height > 0.f ? 2.f : 1.f;

    edgeBRCast = false;
    edgeBLCast = false;
    edgeTRCast = false;
    edgeTLCast = false;

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

    faceLeft.set(-alfSize, 0.f, -alfSize, -height, 0.f, -height + quarterSize, 0.f, quarterSize);
    faceRight.set(alfSize, 0.f, alfSize, -height, 0.f, -height + quarterSize, 0.f, quarterSize);
    faceTop.set(0.f, -quarterSize, alfSize, 0.f, 0.f, quarterSize, -alfSize, 0.f);

    edgeBL.set(0.f, quarterSize, -alfSize, 0.f);
    edgeBR.set(alfSize, 0.f, 0.f, quarterSize);
    edgeTL.set(-alfSize, 0.f, 0.f, -quarterSize);
    edgeTR.set(0.f, -quarterSize, alfSize, 0.f);
}

void Object::setPosition(float x, float y)
{
    position.set(x, y);
}

void Object::draw()
{
    if (height == 0)
    {
        faceTop.draw();
    }
    else
    {
        glPushMatrix();
        glTranslatef(0.f, -height, 0.f);
        faceTop.draw();
        glPopMatrix();
        glColor4f(0.6f, 0.6f, 0.6f, 1.f);
        faceLeft.draw();
        faceRight.draw();
    }
}

void Object::drawOutline()
{
    glColor4f(1.f, 1.f, 1.f, 0.6f);

    if (height == 0)
    {
        faceTop.outline();
    }
    else
    {
        faceLeft.outline();
        faceRight.outline();
        glPushMatrix();
        glTranslatef(0.f, -height, 0.f);
        faceTop.outline();
        glPopMatrix();
    }
}

Quad Object::getEdgeShadow(Segment *edge, float lx, float ly)
{
    float h = height / 64.f;

    return Quad
    (
        edge->p1.x, edge->p1.y,
        edge->p1.x + (edge->p1.x - lx) * h, edge->p1.y + (edge->p1.y - ly) * h,
        edge->p2.x + (edge->p2.x - lx) * h, edge->p2.y + (edge->p2.y - ly) * h,
        edge->p2.x, edge->p2.y
    );
}

void Object::updateShadow(float lx, float ly)
{
    if (shadow && height > 0.f)
    {
        shadowBR = getEdgeShadow(&edgeBR, lx, ly);
        shadowBL = getEdgeShadow(&edgeBL, lx, ly);
        shadowTR = getEdgeShadow(&edgeTR, lx, ly);
        shadowTL = getEdgeShadow(&edgeTL, lx, ly);

        edgeBRCast = doesEdgeCastShadow(&edgeBR, lx, ly);
        edgeBLCast = doesEdgeCastShadow(&edgeBL, lx, ly);
        edgeTRCast = doesEdgeCastShadow(&edgeTR, lx, ly);
        edgeTLCast = doesEdgeCastShadow(&edgeTL, lx, ly);
    }
}

void Object::drawShadow()
{
    if (edgeBRCast) shadowBR.draw();
    if (edgeBLCast) shadowBL.draw();
    if (edgeTRCast) shadowTR.draw();
    if (edgeTLCast) shadowTL.draw();
}

void Object::drawWallShadows(list<Object*> objects)
{
    if (shadow && height > 0.f)
    {
        if (edgeBLCast) faceLeft.draw();
        if (edgeBRCast) faceRight.draw();

        if (!edgeBLCast || !edgeBRCast)
        {
            // Translated objects shadows toward object's position
            Quad objectShadow;

            // Objects screen position
            Vector2 currentSP(getX() - getY(), (getX() + getY()) / 2.f);

            float x, y;

            for (list<Object*>::iterator i = objects.begin(); i != objects.end(); ++ i)
            {
                if ((*i) != this && (*i)->shadowEnabled() && (*i)->getHeight() != 0.f)
                {
                    x = ((*i)->getX() - (*i)->getY()) - currentSP.x;
                    y = ((*i)->getX() + (*i)->getY()) / 2.f - currentSP.y;

                    if ((*i)->edgeTRCast)
                    {
                        objectShadow = (*i)->shadowTR;
                        objectShadow.translate(x, y);
                        drawWallShadow(&objectShadow, height < (*i)->getHeight() ? height : (*i)->getHeight());
                    }

                    if ((*i)->edgeTLCast)
                    {
                        objectShadow = (*i)->shadowTL;
                        objectShadow.translate(x, y);
                        drawWallShadow(&objectShadow, height < (*i)->getHeight() ? height : (*i)->getHeight());
                    }

                    if ((*i)->edgeBRCast)
                    {
                        objectShadow = (*i)->shadowBR;
                        objectShadow.translate(x, y);
                        drawWallShadow(&objectShadow, height < (*i)->getHeight() ? height : (*i)->getHeight());
                    }

                    if ((*i)->edgeBLCast)
                    {
                        objectShadow = (*i)->shadowBL;
                        objectShadow.translate(x, y);
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

    bool c1 = !edgeBLCast && shadow->containsPosition(&edgeBL.p2);
    bool c2 = (!edgeBLCast || !edgeBRCast) && shadow->containsPosition(&edgeBL.p1);
    bool c3 = !edgeBRCast && shadow->containsPosition(&edgeBR.p1);

    if (c1) pointList.push_back(edgeBL.p2);

    if (!edgeBLCast && (!c1 || !c2))
    {
        edgeBL.getIntesectionToSegment(&shadow->s1, &pointList);
        edgeBL.getIntesectionToSegment(&shadow->s2, &pointList);
        edgeBL.getIntesectionToSegment(&shadow->s3, &pointList);
    }

    if (c2) pointList.push_back(edgeBL.p1);

    if (!edgeBRCast && (!c2 || !c3))
    {
        edgeBR.getIntesectionToSegment(&shadow->s1, &pointList);
        edgeBR.getIntesectionToSegment(&shadow->s2, &pointList);
        edgeBR.getIntesectionToSegment(&shadow->s3, &pointList);
    }

    if (c3) pointList.push_back(edgeBR.p1);

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

bool Object::doesEdgeCastShadow(Segment *edge, float lx, float ly)
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


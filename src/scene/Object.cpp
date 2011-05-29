#include "Object.h"

using namespace std;

Object::Object(World *W, float h, bool s) : world(W), height(h), shadow(s)
{
    index = height > 0.f ? 2.f : 1.f;

    edgeCastShadowBR = false;
    edgeCastShadowBL = false;
    edgeCastShadowTR = false;
    edgeCastShadowTL = false;

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

    faceL.clear();
    faceL.addPoint(-alfSize, 0.f);
    faceL.addPoint(-alfSize, -height);
    faceL.addPoint(0.f, -height + quarterSize);
    faceL.addPoint(0.f, quarterSize);
    faceL.computeSegments();

    faceR.clear();
    faceR.addPoint(alfSize, 0.f);
    faceR.addPoint(alfSize, -height);
    faceR.addPoint(0.f, -height + quarterSize);
    faceR.addPoint(0.f, quarterSize);
    faceR.computeSegments();

    faceT.clear();
    faceT.addPoint(0.f, -quarterSize);
    faceT.addPoint(alfSize, 0.f);
    faceT.addPoint(0.f, quarterSize);
    faceT.addPoint(-alfSize, 0.f);
    faceT.computeSegments();
}

void Object::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
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

void Object::updateShadow(Polygon *shadow, Segment *edge, Light *light)
{
    float h = height / 64.f;

    shadow->clear();
    shadow->addPoint(Vector2(edge->getPoint(0)->x, edge->getPoint(0)->y));
    shadow->addPoint(Vector2(edge->getPoint(0)->x + (edge->getPoint(0)->x - light->getX()) * h, edge->getPoint(0)->y + (edge->getPoint(0)->y - light->getY()) * h));
    shadow->addPoint(Vector2(edge->getPoint(1)->x + (edge->getPoint(1)->x - light->getX()) * h, edge->getPoint(1)->y + (edge->getPoint(1)->y - light->getY()) * h));
    shadow->addPoint(Vector2(edge->getPoint(1)->x, edge->getPoint(1)->y));
    shadow->computeSegments();
}

void Object::updateShadows(Light *l)
{
    Light light = *l;
    light.setPosition((l->getX() - position.x) - (l->getY() - position.y), ((l->getX() - position.x) + (l->getY() - position.y)) / 2.f);

    if (shadow && height > 0.f)
    {
        edgeCastShadowBR = shadow && edgeCastShadow(getBaseEdgeBR(), &light);
        edgeCastShadowBL = shadow && edgeCastShadow(getBaseEdgeBL(), &light);
        edgeCastShadowTR = shadow && edgeCastShadow(getBaseEdgeTR(), &light);
        edgeCastShadowTL = shadow && edgeCastShadow(getBaseEdgeTL(), &light);

        if (edgeCastShadowBR) updateShadow(&shadowBR, getBaseEdgeBR(), &light);
        if (edgeCastShadowBL) updateShadow(&shadowBL, getBaseEdgeBL(), &light);
        if (edgeCastShadowTR) updateShadow(&shadowTR, getBaseEdgeTR(), &light);
        if (edgeCastShadowTL) updateShadow(&shadowTL, getBaseEdgeTL(), &light);
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
            Polygon objectShadow;

            // Objects screen position
            Vector2 currentSP(getX() - getY(), (getX() + getY()) / 2.f);
            Vector2 translation;

            for (list<Object*>::iterator i = objects.begin(); i != objects.end(); ++ i)
            {
                if ((*i) != this && (*i)->shadowEnabled() && (*i)->getHeight() != 0.f)
                {
                    translation.x = ((*i)->getX() - (*i)->getY()) - currentSP.x;
                    translation.y = ((*i)->getX() + (*i)->getY()) / 2.f - currentSP.y;

                    // TODO We could try to avoid cloning shadow Polygons

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

void Object::drawWallShadow(Polygon *shadow, float h)
{
    vector<Vector2> pointList;

    unsigned int i;

    bool c1 = !edgeCastShadowBL && shadow->containsPosition(getBaseEdgeBL()->getPoint(1));
    bool c2 = (!edgeCastShadowBL || !edgeCastShadowBR) && shadow->containsPosition(getBaseEdgeBL()->getPoint(0));
    bool c3 = !edgeCastShadowBR && shadow->containsPosition(getBaseEdgeBR()->getPoint(0));

    if (c1) pointList.push_back(*getBaseEdgeBL()->getPoint(1));

    if (!edgeCastShadowBL && (!c1 || !c2))
    {
        for (i = 0; i < shadow->getTotalSegment(); i++)
        {
            getBaseEdgeBL()->collectIntesectionToSegment(shadow->getSegment(i), &pointList);
        }
    }

    if (c2) pointList.push_back(*getBaseEdgeBL()->getPoint(0));

    if (!edgeCastShadowBR && (!c2 || !c3))
    {
        for (i = 0; i < shadow->getTotalSegment(); i++)
        {
            getBaseEdgeBR()->collectIntesectionToSegment(shadow->getSegment(i), &pointList);
        }
    }

    if (c3) pointList.push_back(*getBaseEdgeBR()->getPoint(0));

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

bool Object::edgeCastShadow(Segment *edge, Light *light)
{
    // normal of 2nd point minus 1st point
    float nx = -1 * (edge->getPoint(1)->y - edge->getPoint(0)->y);
    float ny = edge->getPoint(1)->x - edge->getPoint(0)->x;

    // light minus 1st point
    float lx = edge->getPoint(0)->x - light->getX();
    float ly = edge->getPoint(0)->y - light->getY();

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
    return faceT.getSegment(2);
}

Segment* Object::getBaseEdgeBR()
{
    return faceT.getSegment(1);
}

Segment* Object::getBaseEdgeTL()
{
    return faceT.getSegment(3);
}

Segment* Object::getBaseEdgeTR()
{
    return faceT.getSegment(0);
}

Polygon* Object::getShadowBR()
{
    return &shadowBR;
}

Polygon* Object::getShadowBL()
{
    return &shadowBL;
}

Polygon* Object::getShadowTR()
{
    return &shadowTR;
}

Polygon* Object::getShadowTL()
{
    return &shadowTL;
}



#include "Object.h"

using namespace std;

Object::Object(World *w, float h) : world(w), height(h)
{
    index = height > 0.f ? 2.f : 1.f;

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
    if (getHeight() == 64.f)
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

void Object::drawWallShadow(list<Object*> objects)
{
    if (height != 0)
    {
        int n = 0;
        IntersectionObject result;
        float tx = getX() - getY();
        float ty = (getX() + getY()) / 2.f;
        float otx = 0.f;
        float oty = 0.f;
        float h = 0.f;

        glStencilFunc(GL_EQUAL, 1, 1);
        glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

        glPushMatrix();
        glTranslatef(0.f, -height, 0.f);
        faceTop.draw();
        glPopMatrix();

        faceRight.draw();
        faceLeft.draw();

        glStencilFunc(GL_ALWAYS, 1, 1);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        // loop through all objects as o
        for (list<Object*>::iterator i = objects.begin(); i != objects.end(); ++ i)
        {
            // if o has an height
            if ((*i) != this && (*i)->getHeight() != 0.f)
            {
                otx = (*i)->getX() - (*i)->getY() - tx;
                oty = ((*i)->getX() + (*i)->getY()) / 2.f - ty;

                if ((*i)->edgeTRCast)
                {
                    if (ContainFunctions::PointInQuad(edgeBL.p1.x, edgeBL.p1.y, (*i)->shadowTR.p1.x + otx, (*i)->shadowTR.p1.y + oty, (*i)->shadowTR.p2.x + otx, (*i)->shadowTR.p2.y + oty, (*i)->shadowTR.p3.x + otx, (*i)->shadowTR.p3.y + oty, (*i)->shadowTR.p4.x + otx, (*i)->shadowTR.p4.y + oty) && ContainFunctions::PointInQuad(edgeBL.p2.x, edgeBL.p2.y, (*i)->shadowTR.p1.x + otx, (*i)->shadowTR.p1.y + oty, (*i)->shadowTR.p2.x + otx, (*i)->shadowTR.p2.y + oty, (*i)->shadowTR.p3.x + otx, (*i)->shadowTR.p3.y + oty, (*i)->shadowTR.p4.x + otx, (*i)->shadowTR.p4.y + oty))
                    {
                        faceLeft.draw();
                    }
                    else
                    {
                        result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(edgeBL.p1.x, edgeBL.p1.y, edgeBL.p2.x, edgeBL.p2.y, (*i)->shadowTR.p1.x + otx, (*i)->shadowTR.p1.y + oty, (*i)->shadowTR.p2.x + otx, (*i)->shadowTR.p2.y + oty);
                        if (result.NumberOfSolutions() == 1)
                        {
                            h = (getHeight() < (*i)->getHeight() ? getHeight() : (*i)->getHeight());
                            glBegin(GL_QUADS);
                                glVertex2f(result.points[0].x, result.points[0].y);
                                glVertex2f(result.points[0].x, result.points[0].y - h);
                                glVertex2f(edgeBL.p1.x, edgeBL.p1.y - h);
                                glVertex2f(edgeBL.p1.x, edgeBL.p1.y);
                            glEnd();
                        }

                        result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(edgeBL.p1.x, edgeBL.p1.y, edgeBL.p2.x, edgeBL.p2.y, (*i)->shadowTR.p2.x + otx, (*i)->shadowTR.p2.y + oty, (*i)->shadowTR.p3.x + otx, (*i)->shadowTR.p3.y + oty);
                        if (result.NumberOfSolutions() == 1)
                        {
                            h = (getHeight() < (*i)->getHeight() ? getHeight() : (*i)->getHeight());
                            glBegin(GL_QUADS);
                                glVertex2f(result.points[0].x, result.points[0].y);
                                glVertex2f(result.points[0].x, result.points[0].y - h);
                                glVertex2f(edgeBL.p2.x, edgeBL.p2.y - h);
                                glVertex2f(edgeBL.p2.x, edgeBL.p2.y);
                            glEnd();
                        }

                        result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(edgeBL.p1.x, edgeBL.p1.y, edgeBL.p2.x, edgeBL.p2.y, (*i)->shadowTR.p3.x + otx, (*i)->shadowTR.p3.y + oty, (*i)->shadowTR.p4.x + otx, (*i)->shadowTR.p4.y + oty);
                        if (result.NumberOfSolutions() == 1)
                        {
                            h = (getHeight() < (*i)->getHeight() ? getHeight() : (*i)->getHeight());
                            glBegin(GL_QUADS);
                                glVertex2f(result.points[0].x, result.points[0].y);
                                glVertex2f(result.points[0].x, result.points[0].y - h);
                                glVertex2f(edgeBL.p2.x, edgeBL.p2.y - h);
                                glVertex2f(edgeBL.p2.x, edgeBL.p2.y);
                            glEnd();
                        }
                    }

                    if (ContainFunctions::PointInQuad(edgeBR.p1.x, edgeBR.p1.y, (*i)->shadowTR.p1.x + otx, (*i)->shadowTR.p1.y + oty, (*i)->shadowTR.p2.x + otx, (*i)->shadowTR.p2.y + oty, (*i)->shadowTR.p3.x + otx, (*i)->shadowTR.p3.y + oty, (*i)->shadowTR.p4.x + otx, (*i)->shadowTR.p4.y + oty) && ContainFunctions::PointInQuad(edgeBR.p2.x, edgeBR.p2.y, (*i)->shadowTR.p1.x + otx, (*i)->shadowTR.p1.y + oty, (*i)->shadowTR.p2.x + otx, (*i)->shadowTR.p2.y + oty, (*i)->shadowTR.p3.x + otx, (*i)->shadowTR.p3.y + oty, (*i)->shadowTR.p4.x + otx, (*i)->shadowTR.p4.y + oty))
                    {
                        faceRight.draw();
                    }
                    else
                    {
                        result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(edgeBR.p1.x, edgeBR.p1.y, edgeBR.p2.x, edgeBR.p2.y, (*i)->shadowTR.p1.x + otx, (*i)->shadowTR.p1.y + oty, (*i)->shadowTR.p2.x + otx, (*i)->shadowTR.p2.y + oty);
                        if (result.NumberOfSolutions() == 1)
                        {
                            h = (getHeight() < (*i)->getHeight() ? getHeight() : (*i)->getHeight());
                            glBegin(GL_QUADS);
                                glVertex2f(result.points[0].x, result.points[0].y);
                                glVertex2f(result.points[0].x, result.points[0].y - h);
                                glVertex2f(edgeBR.p1.x, edgeBR.p1.y - h);
                                glVertex2f(edgeBR.p1.x, edgeBR.p1.y);
                            glEnd();
                        }

                        result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(edgeBR.p1.x, edgeBR.p1.y, edgeBR.p2.x, edgeBR.p2.y, (*i)->shadowTR.p2.x + otx, (*i)->shadowTR.p2.y + oty, (*i)->shadowTR.p3.x + otx, (*i)->shadowTR.p3.y + oty);
                        if (result.NumberOfSolutions() == 1)
                        {
                            h = (getHeight() < (*i)->getHeight() ? getHeight() : (*i)->getHeight());
                            glBegin(GL_QUADS);
                                glVertex2f(result.points[0].x, result.points[0].y);
                                glVertex2f(result.points[0].x, result.points[0].y - h);
                                glVertex2f(edgeBR.p2.x, edgeBR.p2.y - h);
                                glVertex2f(edgeBR.p2.x, edgeBR.p2.y);
                            glEnd();
                        }

                        result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(edgeBR.p1.x, edgeBR.p1.y, edgeBR.p2.x, edgeBR.p2.y, (*i)->shadowTR.p3.x + otx, (*i)->shadowTR.p3.y + oty, (*i)->shadowTR.p4.x + otx, (*i)->shadowTR.p4.y + oty);
                        if (result.NumberOfSolutions() == 1)
                        {
                            h = (getHeight() < (*i)->getHeight() ? getHeight() : (*i)->getHeight());
                            glBegin(GL_QUADS);
                                glVertex2f(result.points[0].x, result.points[0].y);
                                glVertex2f(result.points[0].x, result.points[0].y - h);
                                glVertex2f(edgeBR.p2.x, edgeBR.p2.y - h);
                                glVertex2f(edgeBR.p2.x, edgeBR.p2.y);
                            glEnd();
                        }
                    }
                }

                if ((*i)->edgeTLCast)
                {
                    if (ContainFunctions::PointInQuad(edgeBL.p1.x, edgeBL.p1.y, (*i)->shadowTL.p1.x + otx, (*i)->shadowTL.p1.y + oty, (*i)->shadowTL.p2.x + otx, (*i)->shadowTL.p2.y + oty, (*i)->shadowTL.p3.x + otx, (*i)->shadowTL.p3.y + oty, (*i)->shadowTL.p4.x + otx, (*i)->shadowTL.p4.y + oty) && ContainFunctions::PointInQuad(edgeBL.p2.x, edgeBL.p2.y, (*i)->shadowTL.p1.x + otx, (*i)->shadowTL.p1.y + oty, (*i)->shadowTL.p2.x + otx, (*i)->shadowTL.p2.y + oty, (*i)->shadowTL.p3.x + otx, (*i)->shadowTL.p3.y + oty, (*i)->shadowTL.p4.x + otx, (*i)->shadowTL.p4.y + oty))
                    {
                        faceLeft.draw();
                    }
                    else
                    {
                        result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(edgeBL.p1.x, edgeBL.p1.y, edgeBL.p2.x, edgeBL.p2.y, (*i)->shadowTL.p1.x + otx, (*i)->shadowTL.p1.y + oty, (*i)->shadowTL.p2.x + otx, (*i)->shadowTL.p2.y + oty);
                        if (result.NumberOfSolutions() == 1)
                        {
                            h = (getHeight() < (*i)->getHeight() ? getHeight() : (*i)->getHeight());
                            glBegin(GL_QUADS);
                                glVertex2f(result.points[0].x, result.points[0].y);
                                glVertex2f(result.points[0].x, result.points[0].y - h);
                                glVertex2f(edgeBL.p1.x, edgeBL.p1.y - h);
                                glVertex2f(edgeBL.p1.x, edgeBL.p1.y);
                            glEnd();
                        }

                        result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(edgeBL.p1.x, edgeBL.p1.y, edgeBL.p2.x, edgeBL.p2.y, (*i)->shadowTL.p2.x + otx, (*i)->shadowTL.p2.y + oty, (*i)->shadowTL.p3.x + otx, (*i)->shadowTL.p3.y + oty);
                        if (result.NumberOfSolutions() == 1)
                        {
                            h = (getHeight() < (*i)->getHeight() ? getHeight() : (*i)->getHeight());
                            glBegin(GL_QUADS);
                                glVertex2f(result.points[0].x, result.points[0].y);
                                glVertex2f(result.points[0].x, result.points[0].y - h);
                                glVertex2f(edgeBL.p1.x, edgeBL.p1.y - h);
                                glVertex2f(edgeBL.p1.x, edgeBL.p1.y);
                            glEnd();
                        }

                        result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(edgeBL.p1.x, edgeBL.p1.y, edgeBL.p2.x, edgeBL.p2.y, (*i)->shadowTL.p3.x + otx, (*i)->shadowTL.p3.y + oty, (*i)->shadowTL.p4.x + otx, (*i)->shadowTL.p4.y + oty);
                        if (result.NumberOfSolutions() == 1)
                        {
                            h = (getHeight() < (*i)->getHeight() ? getHeight() : (*i)->getHeight());
                            glBegin(GL_QUADS);
                                glVertex2f(result.points[0].x, result.points[0].y);
                                glVertex2f(result.points[0].x, result.points[0].y - h);
                                glVertex2f(edgeBL.p2.x, edgeBL.p2.y - h);
                                glVertex2f(edgeBL.p2.x, edgeBL.p2.y);
                            glEnd();
                        }
                    }

                    if (ContainFunctions::PointInQuad(edgeBR.p1.x, edgeBR.p1.y, (*i)->shadowTL.p1.x + otx, (*i)->shadowTL.p1.y + oty, (*i)->shadowTL.p2.x + otx, (*i)->shadowTL.p2.y + oty, (*i)->shadowTL.p3.x + otx, (*i)->shadowTL.p3.y + oty, (*i)->shadowTL.p4.x + otx, (*i)->shadowTL.p4.y + oty) && ContainFunctions::PointInQuad(edgeBR.p2.x, edgeBR.p2.y, (*i)->shadowTL.p1.x + otx, (*i)->shadowTL.p1.y + oty, (*i)->shadowTL.p2.x + otx, (*i)->shadowTL.p2.y + oty, (*i)->shadowTL.p3.x + otx, (*i)->shadowTL.p3.y + oty, (*i)->shadowTL.p4.x + otx, (*i)->shadowTL.p4.y + oty))
                    {
                        faceRight.draw();
                    }
                    else
                    {
                        result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(edgeBR.p1.x, edgeBR.p1.y, edgeBR.p2.x, edgeBR.p2.y, (*i)->shadowTL.p1.x + otx, (*i)->shadowTL.p1.y + oty, (*i)->shadowTL.p2.x + otx, (*i)->shadowTL.p2.y + oty);
                        if (result.NumberOfSolutions() == 1)
                        {
                            h = (getHeight() < (*i)->getHeight() ? getHeight() : (*i)->getHeight());
                            glBegin(GL_QUADS);
                                glVertex2f(result.points[0].x, result.points[0].y);
                                glVertex2f(result.points[0].x, result.points[0].y - h);
                                glVertex2f(edgeBR.p1.x, edgeBR.p1.y - h);
                                glVertex2f(edgeBR.p1.x, edgeBR.p1.y);
                            glEnd();
                        }

                        result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(edgeBR.p1.x, edgeBR.p1.y, edgeBR.p2.x, edgeBR.p2.y, (*i)->shadowTL.p2.x + otx, (*i)->shadowTL.p2.y + oty, (*i)->shadowTL.p3.x + otx, (*i)->shadowTL.p3.y + oty);
                        if (result.NumberOfSolutions() == 1)
                        {
                            h = (getHeight() < (*i)->getHeight() ? getHeight() : (*i)->getHeight());
                            glBegin(GL_QUADS);
                                glVertex2f(result.points[0].x, result.points[0].y);
                                glVertex2f(result.points[0].x, result.points[0].y - h);
                                glVertex2f(edgeBR.p1.x, edgeBR.p1.y - h);
                                glVertex2f(edgeBR.p1.x, edgeBR.p1.y);
                            glEnd();
                        }

                        result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(edgeBR.p1.x, edgeBR.p1.y, edgeBR.p2.x, edgeBR.p2.y, (*i)->shadowTL.p3.x + otx, (*i)->shadowTL.p3.y + oty, (*i)->shadowTL.p4.x + otx, (*i)->shadowTL.p4.y + oty);
                        if (result.NumberOfSolutions() == 1)
                        {
                            h = (getHeight() < (*i)->getHeight() ? getHeight() : (*i)->getHeight());
                            glBegin(GL_QUADS);
                                glVertex2f(result.points[0].x, result.points[0].y);
                                glVertex2f(result.points[0].x, result.points[0].y - h);
                                glVertex2f(edgeBR.p2.x, edgeBR.p2.y - h);
                                glVertex2f(edgeBR.p2.x, edgeBR.p2.y);
                            glEnd();
                        }
                    }
                }
            }
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


#include "Triangle.h"

using namespace std;

Triangle::Triangle(Point *p1, Point *p2, Point *p3)
{
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    update();
}

void Triangle::update()
{
    normal = Vector3Util::Cross(*points[1] - *points[0], *points[2] - *points[0]);
    Vector3Util::Normalize(normal);
}

void Triangle::draw()
{
    glBegin(GL_TRIANGLES);
    glNormal3f(normal.x, normal.y, normal.z);
    drawVertices();
    glEnd();
}

void Triangle::drawOutline()
{
    glBegin(GL_LINE_LOOP);
    drawVertices();
    glEnd();
}

void Triangle::drawVertices()
{
    for (unsigned int i = 0; i < 3; i ++)
    {
        glVertex3f(points[i]->x, points[i]->y, points[i]->z);
    }
}


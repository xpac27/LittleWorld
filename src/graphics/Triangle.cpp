#include "Triangle.h"

using namespace std;

Triangle::Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
    points[0] = Vector3(x1, y1, z1);
    points[1] = Vector3(x2, y2, z2);
    points[2] = Vector3(x3, y3, z3);

    normal = Vector3Util::Cross(points[1] - points[0], points[2] - points[0]);
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
        glVertex3f(points[i].x, points[i].y, points[i].z);
    }
}

void Triangle::translate(Vector3 t)
{
    for (unsigned int i = 0; i < 3; i ++)
    {
        points[i] += t;
    }
}



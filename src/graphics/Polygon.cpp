#include "Polygon.h"

using namespace std;

Polygon::Polygon()
{
}

void Polygon::addTriangle(Point *p1, Point *p2, Point *p3)
{
    triangles.push_back(Triangle(p1, p2, p3));
}

void Polygon::clear()
{
    triangles.clear();
}

void Polygon::draw()
{
    for (unsigned int i = 0; i < triangles.size(); i ++)
    {
        triangles[i].draw();
    }
}

void Polygon::drawOutline()
{
    for (unsigned int i = 0; i < triangles.size(); i ++)
    {
        triangles[i].drawOutline();
    }
}

void Polygon::drawShadow(Vector3 lightPosition)
{
    Vector3 p1, p2;

    for (unsigned int p = 1; p < silhouette.size(); p += 2)
    {
        p1 = (*silhouette[p - 1] - lightPosition);
        p2 = (*silhouette[p] - lightPosition);

        if (p1.y > 0.f)
        {
            p1 *= 100.f;
            p1.y = -10.f;
        }

        if (p2.y > 0.f)
        {
            p2.y *= 100.f;
            p2.y = -10.f;
        }

        glBegin(GL_TRIANGLES);
            glVertex3f(silhouette[p - 1]->x, silhouette[p - 1]->y, silhouette[p - 1]->z);
            glVertex3f(silhouette[p]->x, silhouette[p]->y, silhouette[p]->z);
            glVertex3f(p1.x, p1.y, p1.z);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(silhouette[p]->x, silhouette[p]->y, silhouette[p]->z);
            glVertex3f(p2.x, p2.y, p2.z);
            glVertex3f(p1.x, p1.y, p1.z);
        glEnd();
    }
}

void Polygon::updateConnectivity()
{
    vector<Point*> pointList;

    bool found;

    // Make a list of all unic points
    for (unsigned int t = 0; t < triangles.size(); t ++)
    {
        for (unsigned int p1 = 0; p1 < 3; p1 ++)
        {
            found = false;
            for (unsigned int p2 = 0; p2 < pointList.size(); p2 ++)
            {
                if (triangles[t].points[p1] == pointList[p2])
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                pointList.push_back(triangles[t].points[p1]);
            }
        }
    }

    // Complet the points sharedTriangles list
    for (unsigned int p1 = 0; p1 < pointList.size(); p1 ++)
    {
        pointList[p1]->sharedTriangles.clear();

        for (unsigned int t = 0; t < triangles.size(); t ++)
        {
            for (unsigned int p2 = 0; p2 < 3; p2 ++)
            {
                if (pointList[p1] == triangles[t].points[p2])
                {
                    pointList[p1]->sharedTriangles.push_back(&triangles[t]);
                }
            }
        }
    }
}

void Polygon::updateShadows(Vector3 lightPosition)
{
    silhouette.clear();

    // Compute which triangles are casting shadows
    for (unsigned int t = 0; t < triangles.size(); t ++)
    {
        triangles[t].lighted = Vector3Util::Dot(lightPosition, triangles[t].normal) < 0;
    }

    bool silhouettePoints[3];

    // For each triangle
    for (unsigned int t = 0; t < triangles.size(); t ++)
    {
        // If it casts shadows
        if (!triangles[t].lighted)
        {
            silhouettePoints[0] = false;
            silhouettePoints[1] = false;
            silhouettePoints[2] = false;

            // For each one of its point
            for (unsigned int p = 0; p < 3; p ++)
            {
                for (unsigned int s = 0; s < triangles[t].points[p]->sharedTriangles.size(); s ++)
                {
                    if (triangles[t].points[p]->sharedTriangles[s]->lighted)
                    {
                        silhouettePoints[p] = true;
                    }
                }
            }

            if (silhouettePoints[0] && silhouettePoints[1])
            {
                silhouette.push_back(triangles[t].points[0]);
                silhouette.push_back(triangles[t].points[1]);
            }

            if (silhouettePoints[1] && silhouettePoints[2])
            {
                silhouette.push_back(triangles[t].points[1]);
                silhouette.push_back(triangles[t].points[2]);
            }
        }
    }
}


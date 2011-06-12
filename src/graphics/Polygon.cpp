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
    Point p1, p2;

    glColor4f(0.f, 1.f, 0.f, 1.f);

    for (unsigned int p = 1; p < silhouette.size(); p += 2)
    {
        p1 = Point((*silhouette[p - 1] - lightPosition) * 10.f);
        p2 = Point((*silhouette[p] - lightPosition) * 10.f);

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

    for (unsigned int p = 1; p < silhouette.size(); p += 2)
    {
        p1 = Point((*silhouette[p - 1] - lightPosition) * 10.f);
        p2 = Point((*silhouette[p] - lightPosition) * 10.f);

        glBegin(GL_LINES);
            glVertex3f(silhouette[p - 1]->x, silhouette[p - 1]->y, silhouette[p - 1]->z);
            glVertex3f(silhouette[p]->x, silhouette[p]->y, silhouette[p]->z);

            glVertex3f(silhouette[p]->x, silhouette[p]->y, silhouette[p]->z);
            glVertex3f(p1.x, p1.y, p1.z);

            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(silhouette[p - 1]->x, silhouette[p - 1]->y, silhouette[p - 1]->z);
        glEnd();

        glBegin(GL_LINES);
            glVertex3f(silhouette[p]->x, silhouette[p]->y, silhouette[p]->z);
            glVertex3f(p2.x, p2.y, p2.z);

            glVertex3f(p2.x, p2.y, p2.z);
            glVertex3f(p1.x, p1.y, p1.z);

            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(silhouette[p]->x, silhouette[p]->y, silhouette[p]->z);
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
    bool found, pass;

    silhouette.clear();

    // Compute which triangles are casting shadows
    for (unsigned int t = 0; t < triangles.size(); t ++)
    {
        triangles[t].lighted = Vector3Util::Dot(lightPosition, triangles[t].normal) < 0;
    }

    // For each triangle
    for (unsigned int t = 0; t < triangles.size(); t ++)
    {
        // If it casts shadows
        if (!triangles[t].lighted)
        {
            // For each one of its point
            for (unsigned int p = 0; p < 3; p ++)
            {
                // Compute if that point is part of the silhouette (has no shared triangles or share a non-casting-shadow triangle)
                pass = false;
                //if (triangles[t].points[p]->sharedTriangles.size() == 1)
                //{
                    //pass = true;
                //}
                //else
                //{
                    for (unsigned int s = 0; s < triangles[t].points[p]->sharedTriangles.size(); s ++)
                    {
                        if (triangles[t].points[p]->sharedTriangles[s]->lighted)
                        {
                            pass = true;
                            break;
                        }
                    }
                //}

                // If it's part of the silhouette
                if (pass)
                {
                    // Is it already in the silhouette
                    //found = false;
                    //for (unsigned int p2 = 0; p2 < silhouette.size(); p2 ++)
                    //{
                        //if (triangles[t].points[p] == silhouette[p2])
                        //{
                            //found = true;
                            //break;
                        //}
                    //}

                    // If not add it
                    //if (!found)
                    //{
                        silhouette.push_back(triangles[t].points[p]);
                    //}
                }
            }
        }
    }
}


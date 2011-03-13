#include "Pathfinder.h"

using namespace std;

Pathfinder::Pathfinder()
{
}

void Pathfinder::addStaticObject(StaticObject *o)
{
    staticObjectMap[o->getGridX()][o->getGridY()].push_back(o);
}

vector<Position> Pathfinder::getPath(float x1, float y1, float x2, float y2, float s)
{
    int const dx = (x1 < x2) ? 1 : -1;
    int const dy = (y1 < y2) ? 1 : -1;

    s /= 4.f;

    vector<vector<StaticObject*> > objects;

    if (dx == dy)
    {
        objects.push_back(getTraversingStaticObjects(x1 + s, y1 - s, x2 + s, y2 - s));
        objects.push_back(getTraversingStaticObjects(x1 - s, y1 + s, x2 - s, y2 + s));
    }
    else
    {
        objects.push_back(getTraversingStaticObjects(x1 - s, y1 - s, x2 - s, y2 - s));
        objects.push_back(getTraversingStaticObjects(x1 + s, y1 + s, x2 + s, y2 + s));
    }

    bool pathIsWalkable = true;
    vector<StaticObject*>::iterator i;

    for (unsigned int n = 0; n < objects.size() && pathIsWalkable; n++)
    {
        for (i = objects[n].begin(); i != objects[n].end() && pathIsWalkable; ++ i)
        {
            if ((*i)->isWalkable() == false)
            {
                pathIsWalkable = false;
            }
        }
    }

    vector<Position> path;

    if (pathIsWalkable)
    {
        Position p1(x2, y2);
        path.push_back(p1);
    }

    return path;
}

vector<StaticObject*> Pathfinder::getTraversingStaticObjects(float x1, float y1, float x2, float y2)
{
    vector<StaticObject*> objects;

    //Calculate m and b for the line equation:
    float m = ((y2 / 64.f) - (y1 / 64.f)) / ((x2 / 64.f) - (x1 / 64.f));
    float b = ((y1 + 32.f) / 64.f) - (m * ((x1 + 32.f) / 64.f));

    // Define vars (c=current, n=next, d=direction, e=end)
    float cx = (float)floor((x1 + 32.f) / 64.f);
    float cy = (float)floor((y1 + 32.f) / 64.f);
    float const ex = (float)floor((x2 + 32.f) / 64.f);
    float const ey = (float)floor((y2 + 32.f) / 64.f);
    float const dx = (cx < ex) ? 1.f : -1.f;
    float const dy = (cy < ey) ? 1.f : -1.f;
    float nx, ny;

    unsigned int i = 0;
    unsigned int n = 0;

    for (i = 0; i < staticObjectMap[cx][cy].size(); i ++)
    {
        objects.push_back(staticObjectMap[cx][cy][i]);
    }

    // While we do not reach the end position
    while ((cx != ex || cy != ey) && n < 60)
    {
        // Move 1 tile on x and on y
        nx = cx + dx;
        ny = cy + dy;

        // Find x for the next y value and compare it to the current tile x value
        if (floor((dy == 1) ? ((ny - b) / m) : ((cy - b) / m)) == cx)
        {
            cy = ny;
        }
        else
        {
            cx = nx;
        }
        n ++;

        // Add all the objects in this tile to the list
        for (i = 0; i < staticObjectMap[cx][cy].size(); i ++)
        {
            objects.push_back(staticObjectMap[cx][cy][i]);
        }
    }
    return objects;
}



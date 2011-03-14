#include "Pathfinder.h"

using namespace std;

Pathfinder::Pathfinder()
{
}

void Pathfinder::addStaticObject(StaticObject *o)
{
    int x = o->getGridX();
    int y = o->getGridY();

    if (grid.count(x) == 0 || grid[x].count(y) == 0)
    {
        grid[o->getGridX()][o->getGridY()] = new Point(x, y);
    }
    grid[o->getGridX()][o->getGridY()]->walkable = grid[o->getGridX()][o->getGridY()]->walkable && o->isWalkable();
}

vector<Position*> Pathfinder::getPath(float x1, float y1, float x2, float y2, float s)
{
    vector<Position*> path;

    if (isGridOk((int)floor((x2 + 32.f) / 64.f), (int)floor((y2 + 32.f) / 64.f)))
    {
        cout << "...safe" << endl;
        // TODO CHECK x2 and y2 to see if it's not near to a nonwalkable point

        int const dx = (x1 < x2) ? 1 : -1;
        int const dy = (y1 < y2) ? 1 : -1;

        bool pathIsWalkable = true;

        s /= 4.f;

        list<Point*> points1;
        list<Point*> points2;
        list<Point*>::iterator i;

        points1 = getTraversingPoints(x1 + (s * dx), y1 - (s * dy), x2 + (s * dx), y2 - (s * dy));
        points2 = getTraversingPoints(x1 - (s * dx), y1 + (s * dy), x2 - (s * dx), y2 + (s * dy));

        points1.merge(points2);

        for (i = points1.begin(); i != points1.end() && pathIsWalkable; ++ i)
        {
            pathIsWalkable = (*i)->walkable;
        }

        if (pathIsWalkable)
        {
            path.push_back(new Position(x2, y2));
        }
        else
        {
            path = aStar(x1, y1, x2, y2);
        }
    }

    return path;
}

list<Point*> Pathfinder::getTraversingPoints(float x1, float y1, float x2, float y2)
{
    list<Point*> points;

    // Define vars (c=current, n=next, d=direction, e=end)
    // TODO replace c and e by Points (with getXf and getYf methods)
    float cx = (float)floor((x1 + 32.f) / 64.f);
    float cy = (float)floor((y1 + 32.f) / 64.f);
    float const ex = (float)floor((x2 + 32.f) / 64.f);
    float const ey = (float)floor((y2 + 32.f) / 64.f);
    float const dx = (cx < ex) ? 1.f : -1.f;
    float const dy = (cy < ey) ? 1.f : -1.f;
    float nx, ny;

    //Calculate m and b for the line equation
    float m = (ey - cy) / (ex - cx);
    float b = ey - (m * ex);

    unsigned int n = 0;

    points.push_back(grid[(int)cx][(int)cy]);

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

        // Add this point to the list
        points.push_back(grid[(int)cx][(int)cy]);
    }
    return points;
}

vector<Position*> Pathfinder::aStar(float x1, float y1, float x2, float y2)
{
    Point *start = grid[(int)floor((x1 + 32.f) / 64.f)][(int)floor((y1 + 32.f) / 64.f)];
    Point *end   = grid[(int)floor((x2 + 32.f) / 64.f)][(int)floor((y2 + 32.f) / 64.f)];

    cout << "================" << endl;
    cout << start->x << "x" << start->y << " - " << end->x << "x" << end->y << endl;

    vector<Position*> path;

    Point *current;
    Point *child;

    list<Point*> openList;
    list<Point*> closedList;
    list<Point*>::iterator i;

    unsigned int n = 0;

    openList.push_back(start);
    start->opened = true;

    while (n == 0 || (current != end && n < 10))
    {
        // Look for the smallest F value in the openList and make it the current point
        for (i = openList.begin(); i != openList.end(); ++ i)
        {
            if (i == openList.begin() || (*i)->f < current->f)
            {
                current = (*i);
            }
        }

        // Add the current point to the closedList
        openList.remove(current);
        closedList.push_back(current);
        current->opened = false;
        current->closed = true;

        cout << "curent: " << current->x << "x" << current->y << endl;

        // Get all current's adjacent walkable points
        for (int x = -1; x < 2; x ++)
        {
            for (int y = -1; y < 2; y ++)
            {
                if ((x != 0 || y != 0) && isGridOk(current->x + x, current->x + y))
                {
                    if (!isGridOk(current->x + x, current->y + y) || (x != 0 && y != 0 && !isGridOk(current->x + x, current->y) && !isGridOk(current->x, current->y + y)))
                    {
                        continue;
                    }
                    child = grid[current->x + x][current->y + y];

                    // If it's already in the openList
                    if (child->opened)
                    {
                        // If it has a wroste g score than the one that pass through the current point
                        if (child->g > getGScore(current, child))
                        {
                            // Change parent
                            child->parent = current;
                            cout << "new parent of: " << child->x << "x" << child->y << endl;
                            child->g = getGScore(current, child);
                        }
                    }
                    else
                    {
                        // Add it to the openList with current point as parent
                        openList.push_back(child);
                        child->opened = true;
                        child->parent = current;
                        cout << "parent of: " << child->x << "x" << child->y << endl;
                        child->g = getGScore(current, child);
                        child->h = (abs(end->x - child->x) + abs(end->y - child->y)) * 10;
                        child->f = child->g + child->h;
                    }
                }
            }
        }

        n ++;
    }

    // Reset
    for (i = openList.begin(); i != openList.end(); ++ i)
    {
        (*i)->opened = false;
    }
    for (i = closedList.begin(); i != closedList.end(); ++ i)
    {
        (*i)->closed = false;
    }

    cout << "--------" << endl;

    // Resolve the path
    current = end;
    while (current != start)
    {
        cout << "path: " << current->x << "x" << current->y << endl;
        path.push_back(current->getPosition());
        current = current->parent;
    }

    return path;
}

int Pathfinder::getGScore(Point *p1, Point *p2)
{
    return p1->g + ((p1->x == p2->x || p1->y == p2->y) ? 10 : 14);
}

bool Pathfinder::isGridOk(int x, int y)
{
    return (grid.count(x) != 0 && grid[x].count(y) != 0 && grid[x][y]->walkable && !grid[x][y]->closed);
}


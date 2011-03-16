#include "Pathfinder.h"

using namespace std;

Pathfinder::Pathfinder()
{
}

void Pathfinder::addStaticObject(StaticObject *o)
{
    int x = o->getGridX();
    int y = o->getGridY();

    if (!pointExists(x, y))
    {
        grid[x][y] = new Point(x, y, o->isWalkable());
    }
    else if (o->isWalkable())
    {
        grid[x][y]->walkable = false;
    }
}

vector<Position*> Pathfinder::getPath(float x1, float y1, float x2, float y2, float s)
{
    vector<Position*> path;

    if (pointIsWalkable(coordToGrid(x2), coordToGrid(y2)))
    {
        // Calculate line direction
        int const dx = (x1 < x2) ? 1 : -1;
        int const dy = (y1 < y2) ? 1 : -1;

        bool pathIsWalkable = true;

        s /= 4.f;

        // Get traversing points
        list<Point*> points1;
        list<Point*> points2;
        list<Point*>::iterator i;
        points1 = getTraversingPoints(x1 + (s * dx), y1 - (s * dy), x2 + (s * dx), y2 - (s * dy));
        points2 = getTraversingPoints(x1 - (s * dx), y1 + (s * dy), x2 - (s * dx), y2 + (s * dy));
        points1.merge(points2);

        // Check if the direct path is safe
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
    else
    {
        cout << "not walkable" << endl;
    }

    return path;
}

list<Point*> Pathfinder::getTraversingPoints(float x1, float y1, float x2, float y2)
{
    list<Point*> points;

    // Calculate m and b for the line equation:
    float const m = ((x1 == x2) ? 0.f : ((y2 - y1) / (x2 - x1)));
    float const b = ((y1 + 32.f) / 64.f) - (m * ((x1 + 32.f) / 64.f));

    // Calculate line direction
    float const dx = (x1 < x2) ? 1.f : -1.f;
    float const dy = (y1 < y2) ? 1.f : -1.f;

    // Gather points
    Point *current = getPointFromCoord(x1, y1);
    Point *end = getPointFromCoord(x2, y2);

    points.push_back(current);

    unsigned int n = 0;

    // While we do not reach the end position
    while (current != end && n < 10)
    {
        // Get x next's value and check if it changes
        if (m == 0.f || floor(((((dy == 1) ? current->getYf() + dy : current->getYf()) - b) / m)) == current->getX())
        {
            if (!pointExists(current->getX(), current->getY() + (int)dy))
            {
                return points;
            }
            current = getPoint(current->getX(), current->getY() + (int)dy);
        }
        else
        {
            if (!pointExists(current->getXf() + (int)dx, current->getY()))
            {
                return points;
            }
            current = getPoint(current->getXf() + (int)dx, current->getY());
        }
        n ++;

        // Add this point to the list
        points.push_back(current);
    }
    return points;
}

vector<Position*> Pathfinder::aStar(float x1, float y1, float x2, float y2)
{
    vector<Position*> path;

    // Define points to work with
    Point *start = getPointFromCoord(x1, y1);
    Point *end = getPointFromCoord(x2, y2);
    Point *current;
    Point *child;

    // Define the open and the close list
    list<Point*> openList;
    list<Point*> closedList;
    list<Point*>::iterator i;

    unsigned int n = 0;

    // Add the start point to the openList
    openList.push_back(start);
    start->opened = true;

    while (n == 0 || (current != end && n < 30))
    {
        // Look for the smallest F value in the openList and make it the current point
        for (i = openList.begin(); i != openList.end(); ++ i)
        {
            if (i == openList.begin() || (*i)->getFScore() <= current->getFScore())
            {
                current = (*i);
            }
        }

        // Stop if we reached the end
        if (current == end)
        {
            break;
        }

        // Remove the current point from the openList
        openList.remove(current);
        current->opened = false;

        // Add the current point to the closedList
        closedList.push_back(current);
        current->closed = true;

        // Get all current's adjacent walkable points
        for (int x = -1; x < 2; x ++)
        {
            for (int y = -1; y < 2; y ++)
            {
                // If it's current point then pass
                if (x == 0 && y == 0)
                {
                    continue;
                }

                // Get this point
                child = getPoint(current->getX() + x, current->getY() + y);

                // If it's closed or not walkable then pass
                if (child->closed || !child->walkable)
                {
                    continue;
                }

                // If we are at a corner
                if (x != 0 && y != 0)
                {
                    // if the next horizontal point is not walkable or in the closed list then pass
                    if (!pointIsWalkable(current->getX(), current->getY() + y) || getPoint(current->getX(), current->getY() + y)->closed)
                    {
                        continue;
                    }
                    // if the next vertical point is not walkable or in the closed list then pass
                    if (!pointIsWalkable(current->getX() + x, current->getY()) || getPoint(current->getX() + x, current->getY())->closed)
                    {
                        continue;
                    }
                }

                // If it's already in the openList
                if (child->opened)
                {
                    // If it has a wroste g score than the one that pass through the current point
                    // then its path is improved when it's parent is the current point
                    if (child->getGScore() > child->getGScore(current))
                    {
                        // Change its parent and g score
                        child->setParent(current);
                        child->computeScores(end);
                    }
                }
                else
                {
                    // Add it to the openList with current point as parent
                    openList.push_back(child);
                    child->opened = true;

                    // Compute it's g, h and f score
                    child->setParent(current);
                    child->computeScores(end);
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

    // Resolve the path starting from the end point
    while (current->hasParent() && current != start)
    {
        path.push_back(current->getPosition());
        current = current->getParent();
        n ++;
    }

    return path;
}

Point* Pathfinder::getPoint(int x, int y)
{
    if (pointExists(x, y))
    {
        return grid[x][y];
    }
    else
    {
        cout << "ERROR: failed to gather point " << x << "x" << y << " on grid" << endl;
        return new Point(0, 0, false);
    }
}

Point* Pathfinder::getPointFromCoord(float x, float y)
{
    return getPoint(coordToGrid(x), coordToGrid(y));
}

bool Pathfinder::pointExists(int x, int y)
{
    return (grid.count(x) != 0 && grid[x].count(y) != 0);
}

bool Pathfinder::pointIsWalkable(int x, int y)
{
    return (pointExists(x, y) && grid[x][y]->walkable);
}

int Pathfinder::coordToGrid(float v)
{
    return (int)floor((v + 32.f) / 64.f);
}


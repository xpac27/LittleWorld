#include "Pathfinder.h"

using namespace std;

Pathfinder::Pathfinder()
{
    Tile *tile;

    for (int x = 0; x < TO_GRID(WORLD_WIDTH); x ++)
    {
        for (int y = 0; y < TO_GRID(WORLD_WIDTH); y ++)
        {
            tile = &grid[x][y];

            tile->parent = NULL;
            tile->busy = false;
            tile->opened = false;
            tile->closed = false;
            tile->x = x;
            tile->y = y;
        }
    }
}

void Pathfinder::registerEntity(Entity *entity)
{
    float x = entity->getX();
    float z = entity->getZ();
    float s = entity->getSize();

    for (int i = TO_GRID(x - s / 2.f); i < TO_GRID(x + s / 2.f); i ++)
    {
        for (int j = TO_GRID(z - s / 2.f); j < TO_GRID(z + s / 2.f); j ++)
        {
            if (i < 0 || j < 0 || i > TO_GRID(WORLD_WIDTH) || j > TO_GRID(WORLD_HEIGHT))
            {
                continue;
            }
            grid[i][j].busy = true;
        }
    }
}

vector<Vector3*> Pathfinder::getPath(float fromX, float fromY, float toX, float toY, float s)
{
    vector<Vector3*> path;

    if (isEmpty(TO_GRID(toX), TO_GRID(toY), s))
    {
        if (isPathWalkable(fromX, fromY, toX, toY, s))
        {
            path.push_back(new Vector3(toX, 0.f, toY));
        }
        else
        {
            path = aStar(fromX, fromY, toX, toY, s);
        }
    }
    return path;
}

bool Pathfinder::isPathWalkable(float x1, float y1, float x2, float y2, float s)
{
    // Get traversing tiles
    list<Tile*> tiles = getTraversingTiles(x1, y1, x2, y2);

    // Convert size
    int const size = TO_GRID(s) / 2;

    // Calculate direction
    int const dx = (x1 < x2) ? 1 : -1;
    int const dy = (y1 < y2) ? 1 : -1;

    int gx, gy;

    // Check if direct path is clear
    for (list<Tile*>::iterator t = tiles.begin(); t != tiles.end(); ++ t)
    {
        gy = (*t)->y + (dy > 0 ? size - 1 : -size);
        gx = (*t)->x + (dx > 0 ? size - 1 : -size);

        for (int i = -size; i < size; i ++)
        {
            if ((grid[(*t)->x + i][gy].busy) || (grid[gx][gy = (*t)->y + i].busy)) return false;
        }
    }
    return true;
}

list<Tile*> Pathfinder::getTraversingTiles(float x1, float y1, float x2, float y2)
{
    list<Tile*> tiles;

    // Convert coords
    x1 = (float)TO_GRID(x1);
    y1 = (float)TO_GRID(y1);
    x2 = (float)TO_GRID(x2);
    y2 = (float)TO_GRID(y2);

    // Calculate m and b for the line equation:
    float const m = (x1 == x2) ? 0.f : ((y2 - y1) / (x2 - x1));
    float const b = y1 - (m * x1);

    // Calculate line direction
    int const dx = (x1 < x2) ? 1 : -1;
    int const dy = (y1 < y2) ? 1 : -1;

    // Gather blocks
    Tile *current = &grid[(int)x1][(int)y1];
    Tile *end = &grid[(int)x2][(int)y2];

    tiles.push_back(current);

    unsigned int n = 0;

    // While we do not reach the end position
    while (current != end && n < 100)
    {
        // Get x next's value and check if it changes
        if (m != 0.f && round(((float)(current->y) - b) / m) == current->x)
        {
            if (current->y + dy < 0 || current->y + dy >= TO_GRID(WORLD_HEIGHT))
            {
                return tiles;
            }
            current = &grid[current->x][current->y + dy];
        }
        else
        {
            if (current->x + dx < 0 || current->x + dx >= TO_GRID(WORLD_WIDTH))
            {
                return tiles;
            }
            current = &grid[current->x + dx][current->y];
        }
        n ++;

        // Add this block to the list
        tiles.push_back(current);
    }
    return tiles;
}

vector<Vector3*> Pathfinder::aStar(float x1, float y1, float x2, float y2, float s)
{
    vector<Vector3*> path;

    // Convert size
    int const size = TO_GRID(s) / 2;

    // Define blocks to work with
    Tile *start = &grid[TO_GRID(x1)][TO_GRID(y1)];
    Tile *end = &grid[TO_GRID(x2)][TO_GRID(y2)];
    Tile *current;
    Tile *child;

    // Define the open and the close list
    list<Tile*> openList;
    list<Tile*> closedList;

    list<Tile*>::iterator i;

    unsigned int n = 0;

    // Add the start block to the openList
    openList.push_back(start);
    start->opened = true;

    while (n == 0 || (current != end && n < 100))
    {
        // Look for the smallest F value in the openList and make it the current block
        for (i = openList.begin(); i != openList.end(); ++ i)
        {
            if (i == openList.begin() || (*i)->f <= current->f)
            {
                current = (*i);
            }
        }

        // Stop if we reached the end
        if (current == end)
        {
            break;
        }

        // Remove the current block from the openList
        openList.remove(current);
        current->opened = false;

        // Add the current block to the closedList
        closedList.push_back(current);
        current->closed = true;

        // Get all current's adjacent walkable blocks
        for (int x = -size; x < size + 1; x += size)
        {
            for (int y = -size; y < size + 1; y += size)
            {
                // If it's current block then pass
                if (x == 0 && y == 0
                // or out of bounds
                || current->y + y < 0 || current->y + y >= TO_GRID(WORLD_HEIGHT)
                || current->x + x < 0 || current->x + x >= TO_GRID(WORLD_WIDTH))
                {
                    continue;
                }

                // Get this block
                child = &grid[current->x + x][current->y + y];

                // If it's closed or not walkable then pass
                if (child->closed || !isEmpty(child->x, child->y, s))
                {
                    continue;
                }

                // If we are at a corner
                if (x != 0 && y != 0)
                {
                    // if the next horizontal block is not walkable or in the closed list then pass
                    //if (grid[current->x][current->y + y].busy || grid[current->x][current->y + y].closed)
                    if (!isEmpty(current->x, current->y + y, s) || grid[current->x][current->y + y].closed)
                    {
                        continue;
                    }
                    // if the next vertical block is not walkable or in the closed list then pass
                    //if (grid[current->x + x][current->y].busy || grid[current->x + x][current->y].closed)
                    if (!isEmpty(current->x + x, current->y, s) || grid[current->x + x][current->y].closed)
                    {
                        continue;
                    }
                }

                // If it's already in the openList
                if (child->opened)
                {
                    // If it has a wroste g score than the one that pass through the current block
                    // then its path is improved when it's parent is the current block
                    if (child->g > getGScore(child, current))
                    {
                        // Change its parent and g score
                        child->parent = current;
                        computeScores(child, end);
                    }
                }
                else
                {
                    // Add it to the openList with current block as parent
                    openList.push_back(child);
                    child->opened = true;

                    // Compute it's g, h and f score
                    child->parent = current;
                    computeScores(child, end);
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

    // Resolve the path starting from the end block
    while (current->parent != NULL && current != start)
    {
        path.push_back(new Vector3(current->x * GRID_UNIT, 0.f, current->y * GRID_UNIT));
        current = current->parent;
        n ++;
    }

    return path;
}

bool Pathfinder::isEmpty(int x, int y, float s)
{
    // Convert size
    int const size = TO_GRID(s) / 2;

    if (x < 0 || y < 0 || x > TO_GRID(WORLD_WIDTH) || y > TO_GRID(WORLD_HEIGHT))
    {
        return false;
    }

    for (int i = x - size; i < x + size; i ++)
    {
        for (int j = y - size; j < y + size; j ++)
        {
            if (grid[i][j].busy)
            {
                return false;
            }
        }
    }
    return true;
}

int Pathfinder::getGScore(Tile *t1, Tile *t2)
{
    return t2->g + ((t1->x == t2->x || t1->y == t2->y) ? 10 : 14);
}

int Pathfinder::getHScore(Tile *t1, Tile *t2)
{
    return (abs(t2->x - t1->x) + abs(t2->y - t1->y)) * 10;
}

void Pathfinder::computeScores(Tile *t1, Tile *t2)
{
    t1->g = getGScore(t1, t1->parent);
    t1->h = getHScore(t1, t2);
    t1->f = t1->g + t1->h;
}


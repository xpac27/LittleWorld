#include "Pathfinder.h"

using namespace std;

Pathfinder::Pathfinder()
{
    for (int x = 0; x < TO_GRID(WORLD_WIDTH); x ++)
    {
        for (int y = 0; y < TO_GRID(WORLD_WIDTH); y ++)
        {
            grid[x][y].busy = false;
            grid[x][y].checked = false;
            grid[x][y].x = x;
            grid[x][y].y = y;
        }
    }
}

void Pathfinder::draw(float cameraX, float cameraY)
{
    glPushMatrix();
    glTranslatef(cameraX * -1.f,  0.f, cameraY * -1.f);

    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glEnable(GL_COLOR_MATERIAL); // TODO avoid
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int x = 0; x < TO_GRID(WORLD_WIDTH); x ++)
    {
        for (int y = 0; y < TO_GRID(WORLD_WIDTH); y ++)
        {
            if (grid[x][y].checked == true)
            {
                glColor4f(0.f, 1.f, 0.f, 0.6f);
            }
            else if (grid[x][y].busy == true)
            {
                glColor4f(1.f, 0.f, 0.f, 0.25f);
            }
            else
            {
                glColor4f(1.f, 1.f, 1.f, 0.25f);
            }

            glBegin(GL_QUADS);
            glVertex3f(x * GRID_UNIT, 0.f, y * GRID_UNIT);
            glVertex3f(x * GRID_UNIT + GRID_UNIT, 0.f, y * GRID_UNIT);
            glVertex3f(x * GRID_UNIT + GRID_UNIT, 0.f, y * GRID_UNIT + GRID_UNIT);
            glVertex3f(x * GRID_UNIT, 0.f, y * GRID_UNIT + GRID_UNIT);
            glEnd();
        }
    }

    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);

    glPopMatrix();
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

    for (int x = 0; x < TO_GRID(WORLD_WIDTH); x ++)
    {
        for (int y = 0; y < TO_GRID(WORLD_WIDTH); y ++)
        {
            grid[x][y].checked = false;
        }
    }

    if (isEmpty(toX, toY, s))
    {
        if (isPathWalkable(fromX, fromY, toX, toY, s))
        {
            path.push_back(new Vector3(toX, 0.f, toY));
        }
        //else
        //{
            //path = aStar(fromX, fromY, toX, toY);
        //}
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
        for (int i = -size; i < size; i ++)
        {
            gx = (*t)->x + i;
            grid[gx][gy].checked = true;
            if (grid[gx][gy].busy) return false;
        }

        gx = (*t)->x + (dx > 0 ? size - 1 : -size);
        for (int i = -size; i < size; i ++)
        {
            gy = (*t)->y + i;
            grid[gx][gy].checked = true;
            if (grid[gx][gy].busy) return false;
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

//// TODO handle height of Vector3 positions
//vector<Vector3*> Pathfinder::aStar(float x1, float y1, float x2, float y2)
//{
    //vector<Vector3*> path;

    //// Define blocks to work with
    //Block *start = getBlockFromCoord(x1, y1);
    //Block *end = getBlockFromCoord(x2, y2);
    //Block *current;
    //Block *child;

    //// Define the open and the close list
    //list<Block*> openList;
    //list<Block*> closedList;
    //list<Block*>::iterator i;

    //unsigned int n = 0;

    //// Add the start block to the openList
    //openList.push_back(start);
    //start->opened = true;

    //while (n == 0 || (current != end && n < 50))
    //{
        //// Look for the smallest F value in the openList and make it the current block
        //for (i = openList.begin(); i != openList.end(); ++ i)
        //{
            //if (i == openList.begin() || (*i)->getFScore() <= current->getFScore())
            //{
                //current = (*i);
            //}
        //}

        //// Stop if we reached the end
        //if (current == end)
        //{
            //break;
        //}

        //// Remove the current block from the openList
        //openList.remove(current);
        //current->opened = false;

        //// Add the current block to the closedList
        //closedList.push_back(current);
        //current->closed = true;

        //// Get all current's adjacent walkable blocks
        //for (int x = -1; x < 2; x ++)
        //{
            //for (int y = -1; y < 2; y ++)
            //{
                //// If it's current block then pass
                //if (x == 0 && y == 0)
                //{
                    //continue;
                //}

                //// Get this block
                //child = getBlock(current->getX() + x, current->getY() + y);

                //// If it's closed or not walkable then pass
                //if (child->closed || !child->walkable)
                //{
                    //continue;
                //}

                //// If we are at a corner
                //if (x != 0 && y != 0)
                //{
                    //// if the next horizontal block is not walkable or in the closed list then pass
                    //if (!isEmpty(current->getX(), current->getY() + y) || getBlock(current->getX(), current->getY() + y)->closed)
                    //{
                        //continue;
                    //}
                    //// if the next vertical block is not walkable or in the closed list then pass
                    //if (!isEmpty(current->getX() + x, current->getY()) || getBlock(current->getX() + x, current->getY())->closed)
                    //{
                        //continue;
                    //}
                //}

                //// If it's already in the openList
                //if (child->opened)
                //{
                    //// If it has a wroste g score than the one that pass through the current block
                    //// then its path is improved when it's parent is the current block
                    //if (child->getGScore() > child->getGScore(current))
                    //{
                        //// Change its parent and g score
                        //child->setParent(current);
                        //child->computeScores(end);
                    //}
                //}
                //else
                //{
                    //// Add it to the openList with current block as parent
                    //openList.push_back(child);
                    //child->opened = true;

                    //// Compute it's g, h and f score
                    //child->setParent(current);
                    //child->computeScores(end);
                //}
            //}
        //}

        //n ++;
    //}

    //// Reset
    //for (i = openList.begin(); i != openList.end(); ++ i)
    //{
        //(*i)->opened = false;
    //}
    //for (i = closedList.begin(); i != closedList.end(); ++ i)
    //{
        //(*i)->closed = false;
    //}

    //// Resolve the path starting from the end block
    //while (current->hasParent() && current != start)
    //{
        //path.push_back(current->getPosition());
        //current = current->getParent();
        //n ++;
    //}

    //return path;
//}

//// TODO not needed
//Block* Pathfinder::getBlock(int x, int y)
//{
    //if (blockExists(x, y))
    //{
        //return grid[x][y];
    //}
    //else
    //{
        //// !! We should not fall here
        //return new Block(0, 0, false);
    //}
//}

//// TODO why not
//Block* Pathfinder::getBlockFromCoord(float x, float y)
//{
    //return getBlock(coordToGrid(x), coordToGrid(y));
//}

//// TODO remove
//bool Pathfinder::blockExists(int x, int y)
//{
    //return (grid.count(x) != 0 && grid[x].count(y) != 0);
//}

bool Pathfinder::isEmpty(float x, float y, float s)
{
    if (TO_GRID(x) < 0 || TO_GRID(y) < 0 || TO_GRID(x) > TO_GRID(WORLD_WIDTH) || TO_GRID(y) > TO_GRID(WORLD_HEIGHT))
    {
        return false;
    }

    for (int i = TO_GRID(x - s / 2.f); i < TO_GRID(x + s / 2.f); i ++)
    {
        for (int j = TO_GRID(y - s / 2.f); j < TO_GRID(y + s / 2.f); j ++)
        {
            if (grid[i][j].busy)
            {
                return false;
            }
        }
    }
    return true;
}

//// TODO use definition instead
//int Pathfinder::coordToGrid(float v)
//{
    //return (int)floor((v + 64.f) / 128.f);
//}


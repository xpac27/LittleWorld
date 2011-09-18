#include "Pathfinder.h"

using namespace std;

Pathfinder::Pathfinder()
{
    for (int x = 0; x < TO_GRID(WORLD_WIDTH); x ++)
    {
        for (int y = 0; y < TO_GRID(WORLD_WIDTH); y ++)
        {
            grid[x][y].busy = false;
        }
    }
}

void Pathfinder::registerEntity(Entity *entity)
{
    float x = entity->getX();
    float y = entity->getY();
    float s = entity->getSize();

    for (int i = TO_GRID(x - s / 2.f); i < TO_GRID(x + s / 2.f); i ++)
    {
        for (int j = TO_GRID(y - s / 2.f); j < TO_GRID(y + s / 2.f); j ++)
        {
            grid[i][j].busy = true;
        }
    }
}

vector<Vector3*> Pathfinder::getPath(float fromX, float fromY, float toX, float toY, float s)
{
    vector<Vector3*> path;

    if (isEmpty(toX, toY, s))
    {
        // Calculate line direction
        int const dx = (fromX < toX) ? 1 : -1;
        int const dy = (fromY < toY) ? 1 : -1;

        bool pathIsWalkable = true;

        s /= 2.f;

        // Get traversing blocks
        //list<Block*> blocks1;
        //list<Block*> blocks2;
        //list<Block*>::iterator i;
        //blocks1 = getTraversingBlocks(fromX + (s * dx), fromY - (s * dy), toX + (s * dx), toY - (s * dy));
        //blocks2 = getTraversingBlocks(fromX - (s * dx), fromY + (s * dy), toX - (s * dx), toY + (s * dy));
        //blocks1.merge(blocks2);

        //// Check if the direct path is safe
        //for (i = blocks1.begin(); i != blocks1.end() && pathIsWalkable; ++ i)
        //{
            //pathIsWalkable = (*i)->walkable;
        //}

        //if (pathIsWalkable)
        //{
            //path.push_back(new Vector3(toX, 0.f, toY));
        //}
        //else
        //{
            //path = aStar(fromX, fromY, toX, toY);
        //}
    }

    return path;
}

//// TODO handle height of Vector3 positions
//list<Block*> Pathfinder::getTraversingBlocks(float x1, float y1, float x2, float y2)
//{
    //list<Block*> blocks;

    //// Calculate m and b for the line equation:
    //float const m = ((x1 == x2) ? 0.f : ((y2 - y1) / (x2 - x1)));
    //float const b = ((y1 + 64.f) / 128.f) - (m * ((x1 + 64.f) / 128.f));

    //// Calculate line direction
    //float const dx = (x1 < x2) ? 1.f : -1.f;
    //float const dy = (y1 < y2) ? 1.f : -1.f;

    //// Gather blocks
    //Block *current = getBlockFromCoord(x1, y1);
    //Block *end = getBlockFromCoord(x2, y2);

    //blocks.push_back(current);

    //unsigned int n = 0;

    //// While we do not reach the end position
    //while (current != end && n < 10)
    //{
        //// Get x next's value and check if it changes
        //if (m == 0.f || floor(((((dy == 1) ? current->getYf() + dy : current->getYf()) - b) / m)) == current->getX())
        //{
            //if (!blockExists(current->getX(), current->getY() + (int)dy))
            //{
                //return blocks;
            //}
            //current = getBlock(current->getX(), current->getY() + (int)dy);
        //}
        //else
        //{
            //if (!blockExists(current->getXf() + (int)dx, current->getY()))
            //{
                //return blocks;
            //}
            //current = getBlock(current->getXf() + (int)dx, current->getY());
        //}
        //n ++;

        //// Add this block to the list
        //blocks.push_back(current);
    //}
    //return blocks;
//}

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
    for (int i = TO_GRID(x - s / 2.f); i < TO_GRID(x + s / 2.f); i ++)
    {
        for (int j = TO_GRID(y - s / 2.f); j < TO_GRID(y + s / 2.f); j ++)
        {
            if (grid[i][j].busy) return false;
        }
    }
    return true;
}

//// TODO use definition instead
//int Pathfinder::coordToGrid(float v)
//{
    //return (int)floor((v + 64.f) / 128.f);
//}


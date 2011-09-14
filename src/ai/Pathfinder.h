#ifndef PATHFINDER
#define PATHFINDER

#include "../resources/Conf.h"
#include "../resources/Structs.h"
//#include "../scene/object/StaticObject.h"
//#include "../math/Vector3.h"

#include <iostream>
#include <vector>
#include <list>
#include <map>

class Pathfinder
{
    public:

        Pathfinder();

        //std::vector<Vector3*> getPath(float fromX, float fromY, float toX, float toY, float s);


    private:

        Tile **grid;

        //std::vector<Vector3*> aStar(float x1, float y1, float x2, float y2);
        //std::list<Block*> getTraversingBlocks(float x1, float y1, float x2, float y2);

        //Block* getBlock(int x, int y);
        //Block* getBlockFromCoord(float x, float y);
        //bool blockExists(int x, int y);
        //bool blockIsWalkable(int x, int y);
        //int coordToGrid(float v);
};

#endif


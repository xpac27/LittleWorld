#ifndef PATHFINDER
#define PATHFINDER

#include "../scene/object/StaticObject.h"
#include "../math/Vector3.h"
#include "Block.h"

#include <iostream>
#include <vector>
#include <list>
#include <map>

class Pathfinder
{
    public:

        Pathfinder();

        void addStaticObject(StaticObject *o);

        std::vector<Vector3*> getPath(Vector3 *from, float x, float y, float s);


    private:

        std::vector<Vector3*> aStar(float x1, float y1, float x2, float y2);
        std::list<Block*> getTraversingBlocks(float x1, float y1, float x2, float y2);

        Block* getBlock(int x, int y);
        Block* getBlockFromCoord(float x, float y);

        bool blockExists(int x, int y);
        bool blockIsWalkable(int x, int y);

        int coordToGrid(float v);

        std::map<int, std::map<int, Block*> > grid;
};

#endif


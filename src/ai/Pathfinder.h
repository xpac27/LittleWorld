#ifndef PATHFINDER
#define PATHFINDER

#include "../resources/Conf.h"
#include "../resources/Structs.h"
#include "../scene/Entity.h"
#include "../math/Vector3.h"
//#include "../scene/object/StaticObject.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <map>

class Pathfinder
{
    public:

        Pathfinder();

        void registerEntity(Entity *entity);
        void draw(float cameraX, float cameraY);

        std::vector<Vector3*> getPath(float fromX, float fromY, float toX, float toY, float s);


    private:

        Tile grid[TO_GRID(WORLD_WIDTH)][TO_GRID(WORLD_WIDTH)];

        bool isEmpty(float x, float y, float s);
        bool isPathWalkable(float x1, float y1, float x2, float y2, float s);

        //std::vector<Vector3*> aStar(float x1, float y1, float x2, float y2);
        std::list<Tile*> getTraversingTiles(float x1, float y1, float x2, float y2);

        //Block* getBlock(int x, int y);
        //Block* getBlockFromCoord(float x, float y);
        //bool blockExists(int x, int y);
        //int coordToGrid(float v);
};

#endif


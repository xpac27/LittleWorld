#ifndef PATHFINDER
#define PATHFINDER

#include "../resources/Conf.h"
#include "../resources/Structs.h"
#include "../scene/Entity.h"
#include "../math/Vector3.h"

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

        std::vector<Vector3*> getPath(float fromX, float fromY, float toX, float toY, float s);


    private:

        Tile grid[TO_GRID(WORLD_WIDTH)][TO_GRID(WORLD_WIDTH)];

        int getGScore(Tile *t1, Tile *t2);
        int getHScore(Tile *t1, Tile *t2);

        void computeScores(Tile *t1, Tile *t2);

        bool isEmpty(int x, int y, float s);
        bool isPathWalkable(float x1, float y1, float x2, float y2, float s);

        std::vector<Vector3*> aStar(float x1, float y1, float x2, float y2, float s);
        std::list<Tile*> getTraversingTiles(float x1, float y1, float x2, float y2, float s);

        int toGrid(float i);
        int toGrid(float i, float s);
};

inline int Pathfinder::toGrid(float i)
{
    return std::floor(i / GRID_UNIT);
}

inline int Pathfinder::toGrid(float i, float s)
{
    return std::floor((i - std::fmod(i, s)) / GRID_UNIT);
}

#endif


#ifndef DEF_UTIL_PATHFINDER
#define DEF_UTIL_PATHFINDER

#include "../object/StaticObject.h"
#include "Position.h"

#include <vector>
#include <map>

class Pathfinder
{
    public:

        Pathfinder();

        void addStaticObject(StaticObject *o);

        std::vector<Position> getPath(float x1, float y1, float x2, float y2, float s);



    protected:

        std::vector<StaticObject*> getTraversingStaticObjects(float x1, float y1, float x2, float y2);

        std::map<int, std::map<int, std::vector<StaticObject*> > >staticObjectMap;
};

#endif


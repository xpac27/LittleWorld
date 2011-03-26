#ifndef DEF_DYNAMICOBJECT
#define DEF_DYNAMICOBJECT

#include "../Object.h"
#include "../util/Position.h"
#include "../util/Direction.h"
#include "../util/Pathfinder.h"

#include <iostream>

class World;

class DynamicObject : public Object
{
    public:

        DynamicObject(World *w, float h);

        virtual void update(float time);
        virtual void remove();

        void init(Pathfinder *p);
        void move(float time);
        void setDestination(float x, float y);
        void setDestination(Position *p);
        void setPath(Position *p);
        void resetDestination();


    protected:

        bool isCanMove();

        float speed;


    private:

        std::vector<Position*> path;

        Pathfinder *pathfinder;

        Position destination;
        Direction direction;

        bool canMove;
};

#endif


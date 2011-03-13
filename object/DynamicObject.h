#ifndef DEF_DYNAMICOBJECT
#define DEF_DYNAMICOBJECT

#include "../Object.h"
#include "../util/Position.h"
#include "../util/Direction.h"

#include <iostream>

class World;

class DynamicObject : public Object
{
    public:

        DynamicObject(World *w, float h);

        virtual void update(float time);
        virtual void remove();

        void move(float time);
        void setDestination(float x, float y);
        void setDestination(Position p);
        void setPath(std::vector<Position> p);
        void resetDestination();


    protected:

        float speed;


    private:

        std::vector<Position> path;

        Position destination;
        Direction direction;

        bool canMove;
};

#endif


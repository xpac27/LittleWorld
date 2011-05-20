#ifndef DEF_DYNAMICOBJECT
#define DEF_DYNAMICOBJECT

#include "../Object.h"
#include "../util/primitive/Vector2.h"
#include "../util/Pathfinder.h"

#include <iostream>

class World;

class DynamicObject : public Object
{
    public:

        DynamicObject(World *W, float h, bool s);

        virtual void update(float time);
        virtual void remove();

        void init(Pathfinder *p);
        void move(float time);
        void setDestination(Vector2 *d);
        void setPath(Vector2 *destination);
        void resetDestination();


    protected:

        bool isCanMove();

        float speed;


    private:

        std::vector<Vector2*> path;

        Pathfinder *pathfinder;

        Vector2 destination;
        Vector2 direction;

        bool canMove;
};

#endif


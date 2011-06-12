#ifndef DEF_DYNAMICOBJECT
#define DEF_DYNAMICOBJECT

#include "../Object.h"
#include "../../math/Vector3.h"
#include "../../math/Vector3Util.h"
#include "../../ai/Pathfinder.h"

#include <iostream>

class World;

class DynamicObject : public Object
{
    public:

        DynamicObject(World *W, float h, bool s);

        virtual void update(float time);
        virtual void remove();
        virtual void onNotify(unsigned const int type);

        void init(Pathfinder *p);
        void move(float time);
        void setDestination(Vector3 *d);
        void setPath(float x, float z);
        void resetDestination();


    protected:

        bool isCanMove();

        float speed;


    private:

        std::vector<Vector3*> path;

        Pathfinder *pathfinder;

        Vector3 destination;
        Vector3 direction;

        bool canMove;
};

#endif


#ifndef DEF_DYNAMIC
#define DEF_DYNAMIC

#include "../Entity.h"
#include "../../math/Vector3.h"
#include "../../math/Vector3Util.h"

#include <iostream>
#include <vector>

class World;

class Dynamic : public Entity
{
    public:

        Dynamic(World *W, float s);

        virtual void update(float time);
        virtual void onNotify(unsigned const int type);

        void move(float time);
        void setDestination(Vector3 *d);
        void setPath(float x, float z);
        void resetDestination();


    protected:

        bool isCanMove();

        float speed;


    private:

        std::vector<Vector3*> path;

        Vector3 destination;
        Vector3 direction;

        bool canMove;
};

#endif


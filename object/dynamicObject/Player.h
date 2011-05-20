#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "../DynamicObject.h"
#include "../../World.h"
#include "../../util/primitive/Vector2.h"

#include <boost/bind.hpp>
#include <iostream>

class Player : public DynamicObject
{
    public:

        Player(World *W);

        virtual void draw();
        virtual void update(float time);


    private:

        void onMouseLeftDown();
};

#endif


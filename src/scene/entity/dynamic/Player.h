#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "../Dynamic.h"
#include "../../World.h"

#include <iostream>

class Player : public Dynamic
{
    public:

        Player(World *W, float s);

        virtual void update(float time);
        virtual void onNotify(unsigned const int type);


    private:

        void onMouseLeftDown();
};

#endif


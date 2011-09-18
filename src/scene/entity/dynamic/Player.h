#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "../Dynamic.h"
#include "../../World.h"
#include "../../../resources/Notifications.h"

#include <iostream>

class Player : public Dynamic
{
    public:

        Player(World *w, float s);

        virtual void update(float time);
        virtual void onNotify(unsigned const int type);


    private:

        void onMouseLeftDown();
};

#endif


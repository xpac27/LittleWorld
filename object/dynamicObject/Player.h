#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "../DynamicObject.h"
#include "../../World.h"

#include <SFML/Graphics.hpp>
#include <boost/bind.hpp>

class Player : public DynamicObject
{
    public:

        Player(World *w);

        virtual void init();
        virtual void draw();
        virtual void update(float time);

        void onTest();
};

#endif


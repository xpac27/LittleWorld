#ifndef DEF_GAME
#define DEF_GAME

#include <iostream>
#include <list>
#include "object/DynamicObject.h"
#include "object/dynamicObject/Player.h"

class Game
{
    public:

        Game();
        void init();
        void draw();
        void update(float time);
        void addDynamicObject(DynamicObject *o);


    private:

        std::list<DynamicObject*> dynamicObjectList;
};

#endif


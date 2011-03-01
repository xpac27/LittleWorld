#ifndef DEF_GAME
#define DEF_GAME

#include "object/DynamicObject.h"
#include "object/dynamicObject/Player.h"

#include <iostream>
#include <list>

class Game
{
    public:

        static Game* instance();            // only accessor to game's instance

        void init();
        void draw();
        void update(float time);
        void addDynamicObject(DynamicObject *o);
        void prout();


    private:

        Game();                             // private so that it can  not be called
        Game(const Game &game);             // copy constructor is private
        Game& operator=(const Game &game);  // assignment operator is private

        static Game* p_instance;            // unique instance is private

        std::list<DynamicObject*> dynamicObjectList;
};

#endif


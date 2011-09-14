#ifndef DEF_WORLD
#define DEF_WORLD

#include "../resources/Conf.h"
//#include "../ai/Pathfinder.h"

#include "entity/Dynamic.h"
#include "entity/dynamic/Enemy.h"
#include "entity/dynamic/Player.h"

#include "entity/Static.h"
#include "entity/static/Emitter.h"
#include "entity/static/Decor.h"

#include "Camera.h"

#include <list>
#include <iostream>

class World
{
    public:

        World();

        void draw();
        void update(float time);
        void updateMousePosition(float mouseScreenX, float mouseScreenY);
        void dispatch(unsigned const int type);
        void addPlayer(bool focus);
        void addEnemy(float x, float z);
        void addWallDecor(float x, float z, float h);
        void addFloorDecor(float x, float z);
        void addLight(float x, float z, float y, float r, float g, float b);

        static unsigned const int ON_MOUSE_LEFT_DOWN;
        static unsigned const int ON_WINDOW_RESIZED;

        float mouseX;
        float mouseY;


    private:

        // TODO use static Arrays
        std::list<Dynamic*> dynamicList;
        std::list<Static*>  staticList;
        std::list<Mesh*>    meshList;
        std::list<Sprite*>  spriteList;
        std::list<Light*>   lightList;

        Camera camera;
        //Pathfinder pathfinder;
};

#endif


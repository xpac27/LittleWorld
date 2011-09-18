#ifndef DEF_WORLD
#define DEF_WORLD

#include "../resources/Conf.h"
#include "../ai/Pathfinder.h"
#include "../math/Vector3.h"

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

        std::vector<Vector3*> getPath(Vector3 *position, float toX, float toY, float s);

        float getMouseX();
        float getMouseY();


    private:

        float mouseX;
        float mouseY;

        // TODO use static Arrays
        std::list<Dynamic*> dynamicList;
        std::list<Static*>  staticList;
        std::list<Mesh*>    meshList;
        std::list<Sprite*>  spriteList;
        std::list<Light*>   lightList;

        Camera camera;
        Pathfinder pathfinder;
};

#endif


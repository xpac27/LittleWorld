#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "../resources/Conf.h"

#include "../math/Vector3.h"
#include "../math/Matrix4x4f.h"
#include "../math/Frustum.h"

#include "../graphics/Object.h"
#include "../graphics/object/Mesh.h"
#include "../graphics/object/Light.h"
#include "../graphics/object/Sprite.h"

#include "Entity.h"

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

class Camera
{
    public:

        Camera();

        void update(float time);
        void draw(std::list<Mesh*> *meshes, std::list<Sprite*> *sprites, std::list<Light*> *lights);
        void setFocus(Entity *o);

        float getX();
        float getY();
        float getZ();


    private:

        void drawObject(Object *o);
        void outlineObject(Object *o);
        void drawAllMeshes(std::list<Mesh*> *objects);
        void outlineAllMeshes(std::list<Mesh*> *objects);
        void drawAllSprites(std::list<Sprite*> *objects);
        void outlineAllSprites(std::list<Sprite*> *objects);
        void drawAllLights(std::list<Light*> *objects);
        void outlineAllLights(std::list<Light*> *objects);
        void drawAllShadows(std::list<Mesh*> *objects, Light *l);
        void updateMeshesVisibility(std::list<Mesh*> *objects);
        void updateSpritesVisibility(std::list<Sprite*> *objects);
        void updateViewFrustum();
        void setupLight(Light *l);

        Entity* focus;

        Vector3 position;

        Frustum viewFrustum;

        float speed;
        float tolerance;
        float inertia;
};

#endif


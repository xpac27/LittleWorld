#ifndef DEF_MESH
#define DEF_MESH

#include "Light.h"
#include "../Object.h"
#include "../VBO.h"
#include "../../resources/Structs.h"
#include "../../resources/Conf.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class Mesh : public Object
{
    public:

        Mesh(Entity *e, float size, float height, float red, float green, float blue, float alpha);

        virtual void draw();
        virtual void outline();

        //bool readObject(const char filename); // TODO

        void drawShadow(Light *pLight);

    private:

        void updatePlaneEquations();
        void updateConnectivity();

        unsigned int totalVertex;
        unsigned int totalTriangles;
        unsigned int totalIndexes;

        Vertex vertices[24];
        Triangle triangles[12];
        GLubyte indexes[36];

        VBO *vertexBufferObject;
};

#endif



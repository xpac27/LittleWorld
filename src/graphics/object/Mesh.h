#ifndef DEF_MESH
#define DEF_MESH

#include "Light.h"
#include "../Object.h"
#include "../../resources/Structs.h"
//#include "../../math/Vector3.h"

#include <iostream>
#include <SFML/Graphics.hpp>

//#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// TODO Have an instance of obj instead of the struct and the long constructor

class Mesh : public Object
{
    public:

        Mesh(Entity *e, float size, float height, float red, float green, float blue, float alpha);

        virtual void draw();
        virtual void outline();

        //bool readObject(const char filename); // TODO

        void drawShadow(Light *pLight, bool cap);

        //void updateShadows(Vector3 lightPosition);

    private:

        //void loadData();

        unsigned int totalVertex;
        unsigned int totalTriangles;

        Vertex vertices[24];
        Triangle triangles[12];

        //GLuint vboID;
        //GLuint indexVBOID;
};

#endif



#ifndef DEF_MESH
#define DEF_MESH

#include "../Object.h"
#include "../../math/Vector3.h"

#include <iostream>
#include <SFML/Graphics.hpp>

//#define BUFFER_OFFSET(i) ((char *)NULL + (i))

typedef struct
{
        GLfloat location[3];
        GLfloat tex[2];
        GLfloat normal[3];
        GLfloat color[4];
        GLubyte padding[16]; // Pads the struct out to 64 bytes for performance increase
} Vertex;


class Mesh : public Object
{
    public:

        Mesh(Entity *e, float size, float height, float red, float green, float blue, float alpha);

        virtual void draw();
        virtual void drawOutline();
        //void drawShadow(Vector3 lightPosition, bool cap);
        //void updateShadows(Vector3 lightPosition);
        //void updateConnectivity();

    private:

        void draw(GLenum type);
        //void loadData();

        unsigned int totalVertex;
        unsigned int totalIndex;

        Vertex vertexes[24];
        GLubyte index[36];

        //GLuint vboID;
        //GLuint indexVBOID;
};

#endif



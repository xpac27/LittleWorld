#ifndef DEF_SPRITE
#define DEF_SPRITE

#define X_POS 0
#define Y_POS 1
#define Z_POS 2

#define U_POS 0
#define V_POS 1

#define R_POS 0
#define G_POS 1
#define B_POS 2
#define A_POS 3

#include "../Object.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef DEF_VERTEX
#define DEF_VERTEX
typedef struct
{
        GLfloat location[3];
        GLfloat tex[2];
        GLfloat normal[3];
        GLfloat color[4];
        GLubyte padding[16]; // Pads the struct out to 64 bytes for performance increase
} Vertex;
#endif

// TODO Have an instance of obj instead of the struct and the long constructor

class Sprite : public Object
{
    public:

        Sprite(Entity *e, float size, float height, float red, float green, float blue, float alpha);

        virtual void draw();
        virtual void outline();


    private:

        unsigned int totalVertex;
        unsigned int totalIndex;

        Vertex vertexes[4];
        int index[6];
};

#endif


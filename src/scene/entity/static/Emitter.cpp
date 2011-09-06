#include "Emitter.h"

using namespace std;

Emitter::Emitter(World *W, float x, float y, float z) : Static(W, 0.f)
{
    position.x = x;
    position.y = y;
    position.z = z;
}


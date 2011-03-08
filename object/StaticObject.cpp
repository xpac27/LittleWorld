#include "StaticObject.h"

StaticObject::StaticObject(World *w, float h) : Object(w, h)
{
}

int StaticObject::getGridX()
{
    return position.getGridX();
}

int StaticObject::getGridY()
{
    return position.getGridY();
}


#include "DynamicObject.h"

using namespace std;

DynamicObject::DynamicObject(World *W, float h, bool s) : Object(W, h, s)
{
    canMove = false;
}

void DynamicObject::init(Pathfinder *p)
{
    pathfinder = p;
}

void DynamicObject::update(float time)
{
}

void DynamicObject::remove()
{
}

void DynamicObject::onNotify(unsigned const int type)
{
}

void DynamicObject::move(float time)
{
    if (canMove == true)
    {
        if (Vector3Util::dist(position, destination) > 5.f)
        {
            position += direction * speed * time;
        }
        else if (path.size() > 0)
        {
            setDestination(path.back());
            path.pop_back();
        }
        else
        {
            canMove = false;
        }
    }
}

void DynamicObject::resetDestination()
{
    destination = position;
}

void DynamicObject::setDestination(Vector3 *d)
{
    destination = *d;
    direction = destination - position;
    Vector3Util::Normalize(direction);
    canMove = true;
}

void DynamicObject::setPath(float x, float z)
{
    resetDestination();
    path = pathfinder->getPath(position.x, position.z, x, z, getSize());
    canMove = true;
}

bool DynamicObject::isCanMove()
{
    return canMove;
}


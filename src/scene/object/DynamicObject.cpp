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
            // TODO try thus:
            //position += direction * speed * time;

            position.x += direction.x * speed * time;
            position.y += direction.y * speed * time;
            position.z += direction.z * speed * time;
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
    // TODO try this:
    //destination = d;
    //direction = destination - position;

    destination.x = d->x;
    destination.y = d->y;
    destination.z = d->z;

    direction.x = destination.x - position.x;
    direction.y = destination.y - position.y;
    direction.z = destination.z - position.z;

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


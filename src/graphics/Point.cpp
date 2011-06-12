#include "Point.h"

using namespace std;

Point::Point() : Vector3()
{
}

Point::Point(Vector3 v) : Vector3(v.x, v.y, v.z)
{
}

Point::Point(float x, float y, float z) : Vector3(x, y, z)
{
}


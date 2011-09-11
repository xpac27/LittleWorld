#ifndef FRUSTUM
#define FRUSTUM

#include "Vector3.h"
#include "Matrix4x4f.h"
#include "../resources/Structs.h"

#include <iostream>

class Frustum
{
    public:

        void update(Matrix4x4f projection);

        bool sphereInFrustum(const Vector3 &center, float radius);

        float distanceFromPlaneToPoint(const Plane &plane, const Vector3 &point);

        Plane planes[6];
};

#endif


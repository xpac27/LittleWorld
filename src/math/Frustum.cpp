#include "Frustum.h"

using namespace std;

void Frustum::update(Matrix4x4f projection)
{
    // left clipping plane:
    planes[0].a = projection.m[3]  + projection.m[0];
    planes[0].b = projection.m[7]  + projection.m[4];
    planes[0].c = projection.m[11] + projection.m[8];
    planes[0].d = projection.m[15] + projection.m[12];

    // right clipping plane:
    planes[1].a = projection.m[3]  - projection.m[0];
    planes[1].b = projection.m[7]  - projection.m[4];
    planes[1].c = projection.m[11] - projection.m[8];
    planes[1].d = projection.m[15] - projection.m[12];

    // top clipping plane:
    planes[2].a = projection.m[3]  - projection.m[1];
    planes[2].b = projection.m[7]  - projection.m[5];
    planes[2].c = projection.m[11] - projection.m[9];
    planes[2].d = projection.m[15] - projection.m[13];

    // bottom clipping plane:
    planes[3].a = projection.m[3]  + projection.m[1];
    planes[3].b = projection.m[7]  + projection.m[5];
    planes[3].c = projection.m[11] + projection.m[9];
    planes[3].d = projection.m[15] + projection.m[13];

    // near clipping plane:
    planes[4].a = projection.m[3]  + projection.m[2];
    planes[4].b = projection.m[7]  + projection.m[6];
    planes[4].c = projection.m[11] + projection.m[10];
    planes[4].d = projection.m[15] + projection.m[14];

    // far clipping plane:
    planes[5].a = projection.m[3]  - projection.m[2];
    planes[5].b = projection.m[7]  - projection.m[6];
    planes[5].c = projection.m[11] - projection.m[10];
    planes[5].d = projection.m[15] - projection.m[14];

    float length;

    for (int i = 0; i < 6; ++i)
    {
        length = sqrtf(planes[i].a * planes[i].a + planes[i].b * planes[i].b + planes[i].c * planes[i].c);
        planes[i].a /= length;
        planes[i].b /= length;
        planes[i].c /= length;
        planes[i].d /= length;
    }
}

float Frustum::distanceFromPlaneToPoint(const Plane &plane, const Vector3 &point)
{
    return plane.a * point.x + plane.b * point.y + plane.c * point.z + plane.d;
}

bool Frustum::sphereInFrustum(const Vector3 &center, float radius)
{
    unsigned int within = 0;

    for(unsigned int i = 0; i < 6; i ++)
    {
        if (distanceFromPlaneToPoint(planes[i], center) > -radius)
        {
            within ++;
        }
    }
    return (within == 6) ? true : false;
}


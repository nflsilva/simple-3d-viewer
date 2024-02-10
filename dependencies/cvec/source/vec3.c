#include "cvec/vec3.h"

CVECVec3f* cvecVec3fCreate(float x, float y, float z) 
{
    CVECVec3f* vec = (CVECVec3f*)malloc(sizeof(CVECVec3f));
    vec->x = x;
    vec->y = y;
    vec->z = z;
    return vec;
}

void cvecVec3fTranslate(CVECVec3f* vec, float dx, float dy, float dz)
{
    assert(vec);
    vec->x += dx;
    vec->y += dy;
    vec->z += dz;
}

CVECVec3f* cvecVec3fSub(CVECVec3f* vec0, CVECVec3f* vec1)
{
    return cvecVec3fCreate(
        vec0->x - vec1->x, 
        vec0->y - vec1->y,
        vec0->z - vec1->z);
}

float cvecVec3fDot(CVECVec3f* vec0, CVECVec3f* vec1)
{
    assert(vec0);
    assert(vec1);
    return vec0->x * vec1->x + vec0->y * vec1->y + vec0->z * vec1->z;
}

CVECVec3f* cvecVec3fCross(CVECVec3f* vec0, CVECVec3f* vec1)
{
    assert(vec0);
    assert(vec1);
    return cvecVec3fCreate(
        vec0->y * vec1->z - vec0->z * vec1->y,
        vec0->z * vec1->x - vec0->x * vec1->z,
        vec0->x * vec1->y - vec0->y * vec1->x 
    );
}

float cvecVec3fMagnitude(CVECVec3f* vec)
{
    assert(vec);
    return sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void cvecVec3fNormalize(CVECVec3f* vec)
{
    float mag = cvecVec3fMagnitude(vec);
    if(mag == 0.0f) return;
    vec->x /= mag;
    vec->y /= mag;
    vec->z /= mag;
}
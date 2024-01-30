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
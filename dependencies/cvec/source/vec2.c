#include "cvec/vec2.h"

CVECVec2f* cvecVec2fCreate(float x, float y) 
{
    CVECVec2f* vec = (CVECVec2f*)malloc(sizeof(CVECVec2f));
    vec->x = x;
    vec->y = y;
    return vec;
}

void cvecVec2fTranslate(CVECVec2f* vec, float dx, float dy)
{
    assert(vec);
    vec->x += dx;
    vec->y += dy;
}
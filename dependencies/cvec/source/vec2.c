#include "cvec/vec2.h"

CVEC_Vec2f* cvecVec2fCreate(float x, float y) 
{
    CVEC_Vec2f* vec = (CVEC_Vec2f*)malloc(sizeof(CVEC_Vec2f));
    vec->x = x;
    vec->y = y;
    return vec;
}

void cvecVec2fTranslate(CVEC_Vec2f* vec, float dx, float dy)
{
    if(vec == NULL) return;
    vec->x += dx;
    vec->y += dy;
}
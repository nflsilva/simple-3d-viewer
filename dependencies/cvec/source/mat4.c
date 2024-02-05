#include "cvec/mat4.h"

CVECMat4f* cvecMat4fCreateIdentity() 
{
    CVECMat4f* mat = (CVECMat4f*)malloc(sizeof(CVECMat4f));
    memset(mat, 0, 14);
    return mat;
}

void cvecMat4fTranslate(CVECMat4f* mat, float dx, float dy, float dz)
{
    assert(mat);
    mat->data[12] += dx;
    mat->data[13] += dy;
    mat->data[14] += dz;
}
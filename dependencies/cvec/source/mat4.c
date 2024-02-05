#include "cvec/mat4.h"

static CVECMat4f* cvecCreateZeroMatrix()
{
    CVECMat4f* mat = (CVECMat4f*)malloc(sizeof(CVECMat4f));
    memset(mat->data, 0, sizeof(mat->data));
    return mat;
}

CVECMat4f* cvecMat4fCreateIdentity() 
{
    CVECMat4f* mat = cvecCreateZeroMatrix();
    mat->data[0] = 1;
    mat->data[5] = 1;
    mat->data[10] = 1;
    mat->data[15] = 1;
    return mat;
}

CVECMat4f* cvecMat4fCreatePerspective(float near, float far, float angleOfView)
{
    CVECMat4f* mat = cvecCreateZeroMatrix();
    float scale = 1 / tan(angleOfView * 0.5 * M_PI / 180); 
    mat->data[0] = scale;

    mat->data[5] = scale; 

    mat->data[10] = -(far / (far - near));
    mat->data[11] = -1;
    mat->data[14] = -((far * near) / (far - near));

    return mat;
}

void cvecMat4fTranslate(CVECMat4f* mat, float dx, float dy, float dz)
{
    assert(mat);
    mat->data[12] += dx;
    mat->data[13] += dy;
    mat->data[14] += dz;
}

void cvecMat4fRotateAboutXAxis(CVECMat4f* mat, float angle)
{
    assert(mat);
    float sa = sin(angle * M_PI / 180);
    float ca = cos(angle * M_PI / 180);

    mat->data[5] = ca;
    mat->data[6] = -sa;
    mat->data[9] = sa;
    mat->data[10] = ca;
}

void cvecMat4fRotateAboutYAxis(CVECMat4f* mat, float angle)
{
    assert(mat);
}

void cvecMat4fRotateAboutZAxis(CVECMat4f* mat, float angle)
{
    assert(mat);
}
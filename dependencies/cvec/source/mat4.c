#include "cvec/mat4.h"

CVECMat4F* cvecMat4FCreateIdentity() 
{
    CVECMat4F* mat = (CVECMat4F*)malloc(sizeof(CVECMat4F));
    cvecMat4FSetIdentity(mat);
    return mat;
}

void cvecMat4FSetIdentity(CVECMat4F* mat)
{
    assert(mat);
    memset(mat->data, 0, sizeof(mat->data));
    mat->data[0][0] = 1;
    mat->data[1][1] = 1;
    mat->data[2][2] = 1;
    mat->data[3][3] = 1;
}

void cvecMat4FPerspective(CVECMat4F* mat, float near, float far, float fieldOfView, float aspectRatio)
{
    assert(mat);
    float radFOV = fieldOfView * M_PI / 180;
    float tanFOV = 1 / tan(radFOV * 0.5);
    float range = 1 / (near - far);

    mat->data[0][0] = tanFOV * aspectRatio;
    mat->data[1][1] = tanFOV;
    mat->data[2][2] = far * range;
    mat->data[2][3] = -1;
    mat->data[3][2] = near * far * range;
}

void cvecMat4FTranslation(CVECMat4F* mat, float dx, float dy, float dz)
{
    assert(mat);
    mat->data[3][0] = dx;
    mat->data[3][1] = dy;
    mat->data[3][2] = dz;
}

void cvecMat4FXAxisRotation(CVECMat4F* mat, float angle)
{
    assert(mat);
    float sa = sin(angle * M_PI / 180);
    float ca = cos(angle * M_PI / 180);
    mat->data[1][1] = ca;
    mat->data[1][2] = -sa;
    mat->data[2][1] = sa;
    mat->data[2][2] = ca;
}

void cvecMat4FYAxisRotation(CVECMat4F* mat, float angle)
{
    assert(mat);
    float sa = sin(angle * M_PI / 180);
    float ca = cos(angle * M_PI / 180);
    mat->data[0][0] = ca;
    mat->data[0][2] = -sa;
    mat->data[2][0] = sa;
    mat->data[2][2] = ca;
}

void cvecMat4FZAxisRotation(CVECMat4F* mat, float angle)
{
    assert(mat);
    float sa = sin(angle * M_PI / 180);
    float ca = cos(angle * M_PI / 180);
    mat->data[0][0] = ca;
    mat->data[0][1] = -sa;
    mat->data[1][0] = sa;
    mat->data[1][1] = ca;
}

void cvecMat4FLookAt(CVECMat4F* mat, CVECVec3f* eye, CVECVec3f* target, CVECVec3f* up)
{

    assert(mat);
    CVECVec3f* forward = cvecVec3fSub(target, eye);
    cvecVec3fNormalize(forward);

    CVECVec3f* right = cvecVec3fCross(forward, up);
    cvecVec3fNormalize(right);

    CVECVec3f* newUp = cvecVec3fCross(right, forward);

    mat->data[0][0] = right->x;
    mat->data[0][1] = newUp->x;
    mat->data[0][2] = -forward->x;

    mat->data[1][0] = right->y;
    mat->data[1][1] = newUp->y;
    mat->data[1][2] = -forward->y;

    mat->data[2][0] = right->z;
    mat->data[2][1] = newUp->z;
    mat->data[2][2] = -forward->z;

    mat->data[3][0] = -cvecVec3fDot(right, eye);
    mat->data[3][1] = -cvecVec3fDot(up, eye);
    mat->data[3][2] = cvecVec3fDot(forward, eye);

    free(forward);
    free(right);
    free(newUp);
}

void cvecMat4MatMult(CVECMat4F* mat0, CVECMat4F* mat1)
{
    float temp[16] = { 0 };
    int ti = 0;
    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 4; c++)
        {
            for(int i = 0; i < 4; i++)
            {
                temp[ti] += mat0->data[r][i] * mat1->data[i][c];
            }
            ti++;
        }
    }
    memcpy(mat0->data, temp, sizeof(temp));
}
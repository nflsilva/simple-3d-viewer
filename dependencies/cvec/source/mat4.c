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
    mat->data[0][0] = 1;
    mat->data[1][1] = 1;
    mat->data[2][2] = 1;
    mat->data[3][3] = 1;
    return mat;
}

CVECMat4f* cvecMat4fCreatePerspective(float near, float far, float angleOfView)
{
    CVECMat4f* mat = cvecCreateZeroMatrix();
    float scale = 1 / tan(angleOfView * 0.5 * M_PI / 180); 
    mat->data[0][0] = scale;
    mat->data[1][1] = scale; 

    mat->data[2][2] = -(far / (far - near));
    mat->data[2][3] = -1;
    mat->data[3][2] = -((far * near) / (far - near));

    return mat;
}

CVECMat4f* cvecMat4fCreateTranslate(float dx, float dy, float dz)
{
    CVECMat4f* mat = cvecMat4fCreateIdentity();
    mat->data[3][0] = dx;
    mat->data[3][1] = dy;
    mat->data[3][2] = dz;
    return mat;
}

CVECMat4f* cvecMat4fCreateRotationXAxis(float angle)
{
    CVECMat4f* mat = cvecMat4fCreateIdentity();
    float sa = sin(angle * M_PI / 180);
    float ca = cos(angle * M_PI / 180);

    mat->data[1][1] = ca;
    mat->data[1][2] = -sa;
    mat->data[2][1] = sa;
    mat->data[2][2] = ca;

    return mat;
}

CVECMat4f* cvecMat4fCreateRotationYAxis(float angle)
{
    CVECMat4f* mat = cvecMat4fCreateIdentity();
    float sa = sin(angle * M_PI / 180);
    float ca = cos(angle * M_PI / 180);

    mat->data[0][0] = ca;
    mat->data[0][2] = -sa;
    mat->data[2][0] = sa;
    mat->data[2][2] = ca;

    return mat;
}

CVECMat4f* cvecMat4fCreateRotationZAxis(float angle)
{

}

CVECMat4f* cvecMat4fCreateLookAt(CVECVec3f* eye, CVECVec3f* target, CVECVec3f* up)
{
    CVECVec3f* forward = cvecVec3fSub(target, eye);
    cvecVec3fNormalize(forward);

    CVECVec3f* right = cvecVec3fCross(up, forward);
    cvecVec3fNormalize(right);

    CVECVec3f* actualUp = cvecVec3fCross(forward, right);

    CVECMat4f* mat = cvecMat4fCreateIdentity();
    // 0 4 8
    // 1 5 9
    // 2 6 10
    // 12 13 14

    mat->data[0][0] = right->x;
    mat->data[1][0] = right->y;
    mat->data[2][0] = right->z;

    mat->data[0][1] = actualUp->x;
    mat->data[1][1] = actualUp->y;
    mat->data[2][1] = actualUp->z;

    mat->data[0][2] = -forward->x;
    mat->data[1][2] = -forward->y;
    mat->data[2][2] = -forward->z;

    mat->data[3][0] = -cvecVec3fDot(right, eye);
    mat->data[3][1] = -cvecVec3fDot(actualUp, eye);
    mat->data[3][2] = cvecVec3fDot(forward, eye);
 

    free(forward);
    free(right);
    free(actualUp);

    return mat;
}

void cvecMat4MatMult(CVECMat4f* mat0, CVECMat4f* mat1)
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

    memcpy(mat0->data, temp, sizeof(float) * 16);
}
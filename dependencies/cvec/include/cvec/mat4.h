#ifndef _CVEC_MAT4_H
#define _CVEC_MAT4_H

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "cvec/vec3.h"

/*!
 * Represents a 4x4 matrix of type `float`.
 * @param data The value of `x` coordinate.
 */
typedef struct CVECMat4f {
    float data[4][4];
} CVECMat4f;
/*
     0, 1,   2,  3,
     4, 5,   6,  7,
     8, 9,  10, 11,
    12, 13, 14, 15 
*/


/*!
 * Creates a new 4x4 identity matrix of type `float`.
 * @return A pointer to the new matrix.
 */
CVECMat4f* cvecMat4fCreateIdentity();

/*!
 * Creates a new 4x4 perspective projection matrix of type `float`.
 * @param near The near plane position
 * @param far The far plane position
 * @param left The left plane position
 * @param right the right plane position
 * @param bottom the bottom place position
 * @param top the top plane position
 * @return A pointer to the new matrix.
 */
CVECMat4f* cvecMat4fCreatePerspective(float near, float far, float angleOfView);

/*!
 * Translates a 4x4 identity matrix  of type `float`.
 * @param mat A pointer to the matrix to translate.
 * @param dx The value of delta `x`.
 * @param dy The value of delta `y`.
 * @param dz The value of delta `z`.
 */
CVECMat4f* cvecMat4fCreateTranslate(float dx, float dy, float dz);

CVECMat4f* cvecMat4fCreateRotationXAxis(float angle);

CVECMat4f* cvecMat4fCreateRotationYAxis(float angle);

CVECMat4f* cvecMat4fCreateRotationZAxis(float angle);

CVECMat4f* cvecMat4fCreateLookAt(CVECVec3f* eye, CVECVec3f* target, CVECVec3f* up);

void cvecMat4MatMult(CVECMat4f* mat0, CVECMat4f* mat1);

#endif
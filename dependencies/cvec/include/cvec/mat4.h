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
typedef struct CVECMat4F {
    float data[4][4];
} CVECMat4F;
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
CVECMat4F* cvecMat4FCreateIdentity();

void cvecMat4FSetIdentity(CVECMat4F* mat);

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
void cvecMat4FPerspective(CVECMat4F* mat, float near, float far, float fieldOfView, float aspectRatio);

/*!
 * Translates a 4x4 identity matrix  of type `float`.
 * @param mat A pointer to the matrix to translate.
 * @param dx The value of delta `x`.
 * @param dy The value of delta `y`.
 * @param dz The value of delta `z`.
 */
void cvecMat4FTranslation(CVECMat4F* mat, float dx, float dy, float dz);

void cvecMat4FXAxisRotation(CVECMat4F* mat, float angle);

void cvecMat4FYAxisRotation(CVECMat4F* mat, float angle);

void cvecMat4FZAxisRotation(CVECMat4F* mat, float angle);

void cvecMat4FLookAt(CVECMat4F* mat, CVECVec3f* eye, CVECVec3f* target, CVECVec3f* up);

void cvecMat4MatMult(CVECMat4F* mat0, CVECMat4F* mat1);

#endif
#ifndef _CVEC_MAT4_H
#define _CVEC_MAT4_H

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*!
 * Represents a 4x4 matrix of type `float`.
 * @param data The value of `x` coordinate.
 */
typedef struct CVECMat4f {
    float data[16];
} CVECMat4f;

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
void cvecMat4fTranslate(CVECMat4f* mat, float dx, float dy, float dz);

void cvecMat4fRotateAboutXAxis(CVECMat4f* mat, float angle);

void cvecMat4fRotateAboutYAxis(CVECMat4f* mat, float angle);

void cvecMat4fRotateAboutZAxis(CVECMat4f* mat, float angle);

#endif
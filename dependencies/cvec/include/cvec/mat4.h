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

/*!
 * Sets a specific matrix as identify matrix of type `float`.
 * @param mat tA pointer to the matrix to set.
 */
void cvecMat4FSetIdentity(CVECMat4F* mat);

/*!
 * Sets a specific matrix as perspective projection matrix of type `float`.
 * @param mat A pointer to the matrix to set.
 * @param near The near plane position
 * @param far The far plane position
 * @param fieldOfView The field of view
 * @param aspectRatio The screen aspect ratio
 */
void cvecMat4FPerspective(CVECMat4F* mat, float near, float far, float fieldOfView, float aspectRatio);

/*!
 * Sets a specific matrix as translation matrix of type `float`.
 * @param mat A pointer to the matrix to set.
 * @param tx The value of `x` translation.
 * @param ty The value of `y` translation.
 * @param tz The value of `z` translation.
 */
void cvecMat4FTranslation(CVECMat4F* mat, float tx, float ty, float tz);

/*!
 * Sets a specific matrix as `X` axis rotation matrix of type `float`.
 * @param mat A pointer to the matrix to set.
 * @param angle The rotation angle (degrees)
 */
void cvecMat4FXAxisRotation(CVECMat4F* mat, float angle);

/*!
 * Sets a specific matrix as `Y` axis rotation matrix of type `float`.
 * @param mat A pointer to the matrix to set.
 * @param angle The rotation angle (degrees)
 */
void cvecMat4FYAxisRotation(CVECMat4F* mat, float angle);

/*!
 * Sets a specific matrix as `Z` axis rotation matrix of type `float`.
 * @param mat A pointer to the matrix to set.
 * @param angle The rotation angle (degrees)
 */
void cvecMat4FZAxisRotation(CVECMat4F* mat, float angle);

/*!
 * Sets a specific matrix as look at view matrix of type `float`.
 * @param mat A pointer to the matrix to set.
 * @param eye A pointer to the eye position.
 * @param target A pointer to the target position.
 * @param up A pointer to the up vector.
 */
void cvecMat4FLookAt(CVECMat4F* mat, CVECVec3f* eye, CVECVec3f* target, CVECVec3f* up);

/*!
 * Performs a matrix to matrix multiplication.
 * @param mat0 A pointer to left hand matrix.
 * @param mat1 A pointer to right hand matrix.
 * @warning Stores the result on the left hand matrix.
 */
void cvecMat4MatMult(CVECMat4F* mat0, CVECMat4F* mat1);

/*!
 * Performs a matrix to vector multiplication.
 * @param mat A pointer to the matrix.
 * @param vec A pointer to the vector.
 * @warning Stores the result on input vector.
 */
void cvecMat4Vec3Mult(CVECMat4F* mat, CVECVec3f* vec);

#endif
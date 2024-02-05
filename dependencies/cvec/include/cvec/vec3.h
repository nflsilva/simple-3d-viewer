#ifndef _CVEC_VEC3_H
#define _CVEC_VEC3_H

#include <stdlib.h>
#include <assert.h>

/*!
 * Represents a 3D vector of type `float`.
 * @param x The value of `x` coordinate.
 * @param y The value of `y` coordinate.
 * @param z The value of `z` coordinate.
 */
typedef struct CVECVec3f {
    float x, y, z;
} CVECVec3f;

/*!
 * Creates a new 3D vector of type `float`.
 * @param x The initial value of `x` coordinate.
 * @param y The initial value of `y` coordinate.
 * @param z The initial value of `z` coordinate.
 * @return A pointer to the new vector.
 */
CVECVec3f* cvecVec3fCreate(float x, float y, float z);

/*!
 * Translates a 2D vector of type `float`.
 * @param vec The vector to translate.
 * @param dx The value of delta `x`.
 * @param dy The value of delta `y`.
 * @param dz The value of delta `z`.
 */
void cvecVec3fTranslate(CVECVec3f* vec, float dx, float dy, float dz);

#endif
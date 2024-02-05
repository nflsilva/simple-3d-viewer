#ifndef _CVEC_VEC2_H
#define _CVEC_VEC2_H

#include <stdlib.h>
#include <assert.h>

/*!
 * Represents a 2D vector of type `float`.
 * @param x The value of `x` coordinate.
 * @param y The value of `y` coordinate.
 */
typedef struct CVECVec2f {
    float x, y;
} CVECVec2f;

/*!
 * Creates a new 2D vector of type `float`.
 * @param x The initial value of `x` coordinate.
 * @param y The initial value of `y` coordinate.
 * @return A pointer to the new vector.
 */
CVECVec2f* cvecVec2fCreate(float x, float y);

/*!
 * Translates a 2D vector of type `float`.
 * @param vec The vector to translate.
 * @param dx The value of delta `x`.
 * @param dy The value of delta `y`.
 */
void cvecVec2fTranslate(CVECVec2f* vec, float dx, float dy);

#endif
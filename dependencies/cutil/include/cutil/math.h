#ifndef _CUTIL_MATH_H
#define _CUTIL_MATH_H

/*!
 * Returns input value clipped by two `float`.
 * @param value the original value to clip
 * @param max the minimum value
 * @param min the maximum value
 * @return The clipped value
 * @warning If `max < min` the original is returned
 */
float cutilMathClipf(float value, float max, float min);

/*!
 * Returns the absolute value `float`.
 * @param value the original value
 * @return The absolute value
 */
float cutilMathAbs(float value);

#endif
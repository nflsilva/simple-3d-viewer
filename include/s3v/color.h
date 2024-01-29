#ifndef _S3V_COLOR_H
#define _S3V_COLOR_H

#include <stdlib.h>

/*!
 * Represents a RGBA color.
 * @param red The value of red.
 * @param green The value of green.
 * @param blue The value of blue.
 * @param alpha The value of alpha.
 */
typedef struct S3VColor {
    float red, green, blue, alpha;
} S3VColor;

/*!
 * Creates a new RGBA color.
 * @param r The value of red.
 * @param g The value of green.
 * @param b The value of blue.
 * @param a The value of alpha.
 * @return A pointer to the new color.
 * @warning Input values will be clipped to [`0.0`, `1.0`]
 */
S3VColor* s3vColorCreate(float r, float g, float b, float a);

#endif
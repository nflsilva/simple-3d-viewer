#include "s3v/color.h"

#include "cutil/math.h"

S3VColor* s3vColorCreate(float r, float g, float b, float a)
{
    S3VColor* color = (S3VColor*)malloc(sizeof(S3VColor));
    color->red = cutilMathClipf(r, 0.0, 1.0);
    color->blue = cutilMathClipf(g, 0.0, 1.0);
    color->green = cutilMathClipf(b, 0.0, 1.0);
    color->alpha = cutilMathClipf(a, 0.0, 1.0);
    return color;
}

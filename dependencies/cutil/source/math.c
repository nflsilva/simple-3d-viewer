#include "cutil/math.h"

float cutilMathClipf(float value, float max, float min)
{
    if(max < min) return value;
    if(value > max) return max;
    if(value < min) return min;
    return value;
}

float cutilMathAbs(float value)
{
    if(value < 0) return value * -1.0;
    return value;
}
#include <assert.h>
#include <stdlib.h>

#include "cvec/vec3.h"

int main() 
{
    CVECVec3f* vec = cvecVec3fCreate(1, 2, 3);

    // test translate
    cvecVec3fTranslate(vec, 1, -2, 1);
    assert(vec->x == 2);
    assert(vec->y == 0);
    assert(vec->z == 4); 

    // test dot product
    CVECVec3f* vec1 = cvecVec3fCreate(4, 5, 6);
    assert(cvecVec3fDot(vec, vec1) == 32);

    // test cross product
    CVECVec3f* cross = cvecVec3fCross(vec, vec1);
    assert(cross->x == -20);
    assert(cross->y == 4);
    assert(cross->z == 10);

    // test mag
    assert(cvecVec3fMagnitude(vec) == 4.472136f);

    //test normalize
    cvecVec3fNormalize(vec);
    float normMag = cvecVec3fMagnitude(vec);
    normMag -= (normMag - 1);
    assert(normMag == 1);

    free(vec);
    free(vec1);
    free(cross);
    exit(EXIT_SUCCESS);
}
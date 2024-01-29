#include <assert.h>
#include <stdlib.h>

#include "cvec/vec2.h"

int main() 
{
    CVEC_Vec2f* vec = cvecVec2fCreate(2, 3);

    cvecVec2fTranslate(NULL, 0, 0);
    cvecVec2fTranslate(vec, 1, -2);

    assert(vec->x == 3);
    assert(vec->y == 1); 

    free(vec);
    exit(EXIT_SUCCESS);
}
#include <assert.h>
#include <stdlib.h>

#include "cvec/mat4.h"

int main() 
{
    CVECMat4F* mat0 = cvecMat4FCreateIdentity();
    CVECMat4F* mat1 = cvecMat4FCreateIdentity();
    assert(mat0);
    assert(mat1);

    // setup matrix 0
    for(int r = 0, i = 0; r < 4; r++)
        for(int c = 0; c < 4; c++)
            mat0->data[r][c] = i++;
    
    // test mat0 x identity
    cvecMat4MatMult(mat0, mat1);
    for(int r = 0, i = 0; r < 4; r++)
        for(int c = 0; c < 4; c++)
            assert(mat0->data[r][c] == i++);

    // setup matrix 1
    for(int r = 0, i = 0; r < 4; r++)
        for(int c = 0; c < 4; c++)
            mat1->data[r][c] = i++ * 3;

    // test mat0 x mat1
    cvecMat4MatMult(mat0, mat1);
    float expected[] = { 
         168,  186,  204,  222, 
         456,  522,  588,  654, 
         744,  858,  972, 1086,
        1032, 1194, 1356, 1518
    };

    for(int r = 0; r < 4; r++)
        for(int c = 0; c < 4; c++)
            assert(mat0->data[r][c] == expected[r * 4 + c]);

    free(mat0);
    free(mat1);
    exit(EXIT_SUCCESS);
}
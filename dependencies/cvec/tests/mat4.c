#include <assert.h>
#include <stdlib.h>

#include "cvec/mat4.h"
#include "cvec/vec3.h"

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

    mat0->data[0][0] = 2;
    mat0->data[0][1] = -1;
    mat0->data[0][2] = 3;
    mat0->data[0][3] = 5;

    mat0->data[1][0] = 1;
    mat0->data[1][1] = 3;
    mat0->data[1][2] = 0;
    mat0->data[1][3] = 4;
    
    mat0->data[2][0] = 3;
    mat0->data[2][1] = 0;
    mat0->data[2][2] = -1;
    mat0->data[2][3] = -2;

    mat0->data[3][0] = 0;
    mat0->data[3][1] = 0;
    mat0->data[3][2] = 0;
    mat0->data[3][3] = 1;

    CVECVec3f* vec = cvecVec3fCreate(2, 0, -1);
    cvecMat4Vec3Mult(mat0, vec);

    free(mat0);
    free(mat1);
    free(vec);
    exit(EXIT_SUCCESS);
}
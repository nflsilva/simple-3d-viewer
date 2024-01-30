#ifndef _S3V_MESH_H
#define _S3V_MESH_H

#include "cvec/vec3.h"

typedef struct S3VMesh {
    CVECVec3f* vertices;
    int* indexes;
} S3VMesh;

S3VMesh* s3vMeshCreate();

void s3vMeshDestroy(S3VMesh* mesh);

#endif
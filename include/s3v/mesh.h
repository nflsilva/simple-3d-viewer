#ifndef _S3V_MESH_H
#define _S3V_MESH_H

#include <assert.h>
#include <glad/glad.h>
#include <stdlib.h>
#include <string.h>

#include "s3v/s3v.h"
#include "cutil/list.h"

#define S3V_BATCH_MAX_ATTRIBUTES 20

/*!
 * 
 */
typedef struct S3VMeshAttribute {
    GLuint glVBO;
    unsigned int sizeInBytes;
    void* data;
} S3VMeshAttribute;

typedef struct S3VMesh {
    GLuint glVAO;
    S3VMeshAttribute indexAttribute;
    S3VMeshAttribute attributes[S3V_BATCH_MAX_ATTRIBUTES];
    unsigned int nAttributes;
} S3VMesh;

void s3vMeshSetIndexAttribute(S3VMesh* mesh, unsigned int size, unsigned int* buffer);

void s3vMeshAttributeAdd(S3VMesh* mesh, unsigned int nComponents, unsigned int size, int type, void* buffer);

void s3vMeshAttributeDestroy(S3VMeshAttribute* attribute);

S3VMesh* s3vMeshCreate();

void s3vMeshDestroy(S3VMesh* mesh);

void s3vMeshBind(S3VMesh* mesh);

void s3vMeshUnbind();

#endif
#ifndef _S3V_MESH_H
#define _S3V_MESH_H

#include <assert.h>
#include <glad/glad.h>
#include <stdlib.h>
#include <string.h>

#include "s3v/s3v.h"
#include "cutil/list.h"
#include "cutil/filebrowser.h"
#include "cutil/vector.h"
#include "cutil/hash_table.h"

#define S3V_BATCH_MAX_ATTRIBUTES 20

/*!
 * 
 */
typedef struct S3VMeshVertex {
    float position[3];
    float normal[3];
    float uv[2];
} S3VMeshVertex;

typedef struct S3VMesh {
    // mesh has a simple VAO and VBO, for now
    GLuint glVAO;
    GLuint glVBO;
    GLuint glEBO;
    unsigned int nElements, maxElements;
    float maxDistance;
} S3VMesh;

S3VMesh* s3vMeshCreate();

void s3vMeshInit(S3VMesh* mesh, S3VMeshVertex* vertices, int nVertices, unsigned int* indices, int nIndices);

void s3vMeshDestroy(S3VMesh* mesh);

void s3vMeshBind(S3VMesh* mesh);

void s3vMeshUnbind();

void s3vMeshCreateFromFile(const char* directoryPath, S3VMesh* mesh);

#endif
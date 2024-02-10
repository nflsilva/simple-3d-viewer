#ifndef _S3V_RENDERER_H
#define _S3V_RENDERER_H

#include <assert.h>

#include "cvec/mat4.h"
#include "s3v/mesh.h"
#include "s3v/shader.h"

typedef struct S3VRenderer {
    S3VShader* shader;
    S3VMesh* mesh;
    CVECMat4f* projectionMatrix;
    CVECMat4f* modelMatrix;
    CVECMat4f* viewMatrix;
} S3VRenderer;

void s3vRendererInit();

void s3vRendererDestroy();

void s3vRendererRender();

void s3vRendererRenderMesh(S3VMesh* mesh);

#endif
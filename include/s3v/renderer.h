#ifndef _S3V_RENDERER_H
#define _S3V_RENDERER_H

#include <assert.h>

#include "cvec/mat4.h"
#include "s3v/context.h"
#include "s3v/mesh.h"
#include "s3v/shader.h"

typedef struct S3VRenderer {
    S3VShader* shader;
    S3VMesh* mesh;
    CVECMat4F* pvmMatrix;
    CVECMat4F* projectionMatrix;
    CVECMat4F* modelMatrix;
    CVECMat4F* viewMatrix;
    float aspectRatio;
} S3VRenderer;

void s3vRendererInit();

void s3vRendererDestroy();

void s3vRendererRender(S3VContext* context);

void s3vRendererRenderMesh(S3VMesh* mesh);

#endif
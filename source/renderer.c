#include "s3v/renderer.h"

static S3VRenderer* renderer;

void s3vRendererInit() {
    renderer = (S3VRenderer*) malloc(sizeof(S3VRenderer));
}

void s3vRendererDestroy() {
    assert(renderer);
    s3vShaderDestroy(renderer->shader);
    s3vMeshDestroy(renderer->mesh);
    free(renderer);
}

void s3vRendererRenderMesh(S3VMesh* mesh) {
    assert(renderer);
    renderer->mesh = mesh;
}
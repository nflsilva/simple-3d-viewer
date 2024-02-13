#include "s3v/renderer.h"

static S3VRenderer* renderer;
static CVECMat4F* rot;

void s3vRendererInit() 
{
    renderer = (S3VRenderer*) malloc(sizeof(S3VRenderer));
    renderer->shader = s3vShaderCreateDefaultShader();
    renderer->pvmMatrix = cvecMat4FCreateIdentity();
    renderer->projectionMatrix = cvecMat4FCreateIdentity();
    renderer->modelMatrix = cvecMat4FCreateIdentity();
    renderer->viewMatrix = cvecMat4FCreateIdentity();

    CVECVec3f* eye = cvecVec3fCreate(2.5, 2.5, 2.5);
    CVECVec3f* lookAt = cvecVec3fCreate(0, 0, 0);
    CVECVec3f* up = cvecVec3fCreate(0, 1, 0);
    cvecMat4FLookAt(renderer->viewMatrix, eye, lookAt, up);

    free(eye);
    free(lookAt);
    free(up);

    //rot = cvecMat4FXAxisRotation(1.0f);
    //cvecMat4MatMult(rot, cvecMat4fCreateRotationYAxis(1.0f));
    //cvecMat4MatMult(rot, cvecMat4fCreateRotationZAxis(1.0f));
}

void s3vRendererDestroy() 
{
    assert(renderer);
    s3vShaderDestroy(renderer->shader);
    s3vMeshDestroy(renderer->mesh);
    free(renderer);
}

void s3vRendererRender(S3VContext* context) 
{
    assert(renderer);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2, 0.2, 0.2, 1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //cvecMat4MatMult(renderer->modelMatrix, rot);
    float aspectRatio = context->windowHeight / (float)context->windowWidth;
    cvecMat4FPerspective(renderer->projectionMatrix, 0.1, 1000, 90, aspectRatio);

    cvecMat4FSetIdentity(renderer->pvmMatrix);
    cvecMat4MatMult(renderer->pvmMatrix, renderer->modelMatrix);
    cvecMat4MatMult(renderer->pvmMatrix, renderer->viewMatrix);
    cvecMat4MatMult(renderer->pvmMatrix, renderer->projectionMatrix);

    s3vShaderBind(renderer->shader);
    s3vShaderSetUniformMat4F(renderer->shader, "uni_pvmMatrix", renderer->pvmMatrix->data);
    s3vMeshBind(renderer->mesh);
    glDrawElements(GL_TRIANGLES, renderer->mesh->indexAttribute.count, GL_UNSIGNED_INT, 0);

    s3vShaderUnbind();
}

void s3vRendererRenderMesh(S3VMesh* mesh) 
{
    assert(renderer);
    renderer->mesh = mesh;
}
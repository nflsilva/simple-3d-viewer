#include "s3v/renderer.h"

static S3VRenderer* renderer;
static CVECVec3f* eye;
static CVECVec3f* lookAt;
static CVECVec3f* up;
static CVECMat4F* xRotation;
static CVECMat4F* yRotation;

void s3vRendererInit() 
{
    renderer = (S3VRenderer*) malloc(sizeof(S3VRenderer));
    renderer->shader = s3vShaderCreateDefaultShader();
    renderer->pvmMatrix = cvecMat4FCreateIdentity();
    renderer->projectionMatrix = cvecMat4FCreateIdentity();
    renderer->modelMatrix = cvecMat4FCreateIdentity();
    renderer->viewMatrix = cvecMat4FCreateIdentity();
    xRotation = cvecMat4FCreateIdentity();
    yRotation = cvecMat4FCreateIdentity();

    eye = cvecVec3fCreate(0, 0, 35);
    lookAt = cvecVec3fCreate(0, 0, 0);
    up = cvecVec3fCreate(0, 1, 0);
    cvecMat4FLookAt(renderer->viewMatrix, eye, lookAt, up);
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

    float aspectRatio = context->windowHeight / (float)context->windowWidth;
    cvecMat4FPerspective(renderer->projectionMatrix, 0.1, 1000, 90, aspectRatio);

    if(context->mouseButton)
    {
        //cvecMat4FXAxisRotation(xRotation, 0.05 * context->mouseDeltaY);
        cvecMat4FYAxisRotation(yRotation, -0.01 * context->mouseDeltaX);
        cvecMat4MatMult(renderer->modelMatrix, xRotation);
        cvecMat4MatMult(renderer->modelMatrix, yRotation);
    }

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
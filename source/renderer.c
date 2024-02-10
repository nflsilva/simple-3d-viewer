#include "s3v/renderer.h"

static S3VRenderer* renderer;
static CVECMat4f* rot;

void s3vRendererInit() 
{
    renderer = (S3VRenderer*) malloc(sizeof(S3VRenderer));
    renderer->shader = s3vShaderCreateDefaultShader();
    renderer->projectionMatrix = cvecMat4fCreatePerspective(0.1, 1000, 90);
    renderer->modelMatrix = cvecMat4fCreateIdentity();
    //cvecMat4fCreateTranslate(0.0f, 0.0f, -10.0f);

    CVECVec3f* eye = cvecVec3fCreate(0, 0, 5);
    CVECVec3f* lookAt = cvecVec3fCreate(0, 0, 0);
    CVECVec3f* up = cvecVec3fCreate(0, 1, 0);
    renderer->viewMatrix = cvecMat4fCreateLookAt(eye, lookAt, up);
    free(eye);
    free(lookAt);
    free(up);

    rot = cvecMat4fCreateRotationXAxis(1.0f);
    cvecMat4MatMult(rot, cvecMat4fCreateRotationYAxis(1.0f));
}

void s3vRendererDestroy() 
{
    assert(renderer);
    s3vShaderDestroy(renderer->shader);
    s3vMeshDestroy(renderer->mesh);
    free(renderer);
}

void s3vRendererRender() 
{
    assert(renderer);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2, 0.2, 0.2, 1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    s3vShaderBind(renderer->shader);
    s3vShaderSetUniformMat4F(renderer->shader, "uni_projectionMatrix", renderer->projectionMatrix->data);
    s3vShaderSetUniformMat4F(renderer->shader, "uni_modelMatrix", renderer->modelMatrix->data);
    s3vShaderSetUniformMat4F(renderer->shader, "uni_viewMatrix", renderer->viewMatrix->data);

    cvecMat4MatMult(renderer->modelMatrix, rot);

    s3vMeshBind(renderer->mesh);
    glDrawElements(GL_TRIANGLES, renderer->mesh->indexAttribute.count, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    s3vShaderUnbind();
}

void s3vRendererRenderMesh(S3VMesh* mesh) 
{
    assert(renderer);
    renderer->mesh = mesh;
}
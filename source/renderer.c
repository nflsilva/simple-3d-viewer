#include "s3v/renderer.h"

static S3VRenderer* renderer;

void s3vRendererInit() 
{
    renderer = (S3VRenderer*) malloc(sizeof(S3VRenderer));
    renderer->shader = s3vShaderCreateDefaultShader();
    renderer->projectionMatrix = cvecMat4fCreatePerspective(0.1, 100, 110);
    renderer->modelMatrix = cvecMat4fCreateIdentity();
    cvecMat4fTranslate(renderer->modelMatrix, 0.0f, -1.0f, -1.0f);
    cvecMat4fRotateAboutXAxis(renderer->modelMatrix,  5.0f);
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
    cvecMat4fTranslate(renderer->modelMatrix, 0.0f, 0.0f, -0.001f);


    s3vMeshBind(renderer->mesh);
    glDrawElements(GL_TRIANGLES, 6 * 3 * 2, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    s3vShaderUnbind();
}

void s3vRendererRenderMesh(S3VMesh* mesh) 
{
    assert(renderer);
    renderer->mesh = mesh;
}
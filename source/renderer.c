#include "s3v/renderer.h"

static S3VRenderer* renderer;

void s3vRendererInit() 
{
    renderer = (S3VRenderer*) malloc(sizeof(S3VRenderer));
    renderer->shader = s3vShaderCreateDefaultShader();
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

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.2, 0.2, 1);

    s3vShaderBind(renderer->shader);

    // render mesh
    s3vMeshBind(renderer->mesh);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    s3vShaderUnbind();
}

void s3vRendererRenderMesh(S3VMesh* mesh) 
{
    assert(renderer);
    renderer->mesh = mesh;
}
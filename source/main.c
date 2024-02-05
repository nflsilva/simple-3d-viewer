#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "s3v/mesh.h"
#include "s3v/renderer.h"
#include "s3v/shader.h"
#include "s3v/window.h"

#include "cutil/filebrowser.h"

int main()
{

    assert(s3vWindowOpen(1280, 720, "s3v") == S3V_SUCCESS);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };  

    unsigned int indices[] = { 
        0, 1, 2 
    }; 

    S3VMesh* mesh = s3vMeshCreate();
    s3vMeshAttributeAdd(mesh, 3, 3, GL_FLOAT, vertices);
    s3vMeshSetIndexAttribute(mesh, 3, indices);
        
    s3vRendererInit();
    s3vRendererRenderMesh(mesh);

    while(!s3vWindowShouldClose()) 
    {
        s3vRendererRender();
        s3vWindowUpdate();
    }

    s3vRendererDestroy();
    s3vWindowClose();

    exit(EXIT_SUCCESS);
}
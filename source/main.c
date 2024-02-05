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
        // Front face
        -0.5f, -0.5f,  0.5f,    // 0
         0.5f, -0.5f,  0.5f,    // 1
         0.5f,  0.5f,  0.5f,    // 2
        -0.5f,  0.5f,  0.5f,    // 3

        // Back face
        -0.5f, -0.5f, -0.5f,    // 4
         0.5f, -0.5f, -0.5f,    // 5
         0.5f,  0.5f, -0.5f,    // 6
        -0.5f,  0.5f, -0.5f     // 7
    };  

    unsigned int indices[] = { 
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Right face
        1, 5, 6,
        6, 2, 1,

        // Back face
        5, 4, 7,
        7, 6, 5,

        // Left face
        4, 0, 3,
        3, 7, 4,

        // Bottom face
        4, 5, 1,
        1, 0, 4,

        // Top face
        3, 2, 6,
        6, 7, 3
    }; 

    S3VMesh* mesh = s3vMeshCreate();
    s3vMeshAttributeAdd(mesh, 3, 8, GL_FLOAT, vertices);
    s3vMeshSetIndexAttribute(mesh, 6 * 3 * 2, indices);
        
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
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "s3v/shader.h"
#include "s3v/window.h"

#include "cutil/filebrowser.h"

int main()
{

    assert(s3vWindowOpen(1280, 720, "s3v") == S3V_SUCCESS);
    // testing shader creation and compilation
    //S3VShader* shapeShader = s3vShaderCreateShapeShader();
    //assert(shapeShader != NULL);

    while(!s3vWindowShouldClose()) 
    {
        s3vWindowUpdate();
    }

    // cleanup 
    //s3vShaderDestroy(shapeShader);
    s3vWindowClose();

    exit(EXIT_SUCCESS);
}
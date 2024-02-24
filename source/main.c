#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "s3v/mesh.h"
#include "s3v/renderer.h"
#include "s3v/shader.h"
#include "s3v/context.h"
#include "s3v/window.h"

#include "cutil/filebrowser.h"

int main()
{

    assert(s3vWindowOpen(1280, 720, "s3v") == S3V_SUCCESS);
    s3vRendererInit();

    S3VContext context;
    while(!s3vWindowShouldClose()) 
    {
        s3vWindowUpdate(&context);
        s3vRendererRender(&context);
        s3vWindowRender(&context);
    }

    s3vRendererDestroy();
    s3vWindowClose();

    exit(EXIT_SUCCESS);
}
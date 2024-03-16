#include "s3v/ui.h"


#include "s3v/context.h"
#include "s3v/renderer.h"
#include "cutil/filebrowser.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear.h"
#include "nuklear_glfw_gl3.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

#define TOP_TOOLBAR_HEIGHT 30
#define SIDE_TOOLBAR_WIDTH 150

static struct nk_glfw glfw = { 0 };
static struct nk_context *ctx;
static int width, height;
static int renderFileBrowser = 0;
static char fpsBuffer[25] = { '\0' };
static CUTILFileBrowser* fileBrowser = NULL;

extern GLFWwindow* s3vWindow;
extern S3VRenderer* renderer;

void s3vUIInit()
{
    assert(s3vWindow);
    ctx = nk_glfw3_init(&glfw, s3vWindow, NK_GLFW3_INSTALL_CALLBACKS);
    {
        struct nk_font_atlas *atlas;
        nk_glfw3_font_stash_begin(&glfw, &atlas);
        nk_glfw3_font_stash_end(&glfw);
    }
}

void s3vUIRender(S3VContext* context)
{
    width = context->windowWidth;
    height = context->windowHeight;
    nk_glfw3_new_frame(&glfw);

    s3vUIRenderTopToolbar(context);

    if(renderFileBrowser)
        s3vUIRenderFilebrowser();

    nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}

void s3vUIFinish()
{
    nk_glfw3_shutdown(&glfw);
}

void s3vUIRenderTopToolbar(S3VContext* context)
{
    if (nk_begin(ctx, "top-tool-bar", nk_rect(0, 0, width, TOP_TOOLBAR_HEIGHT), NK_WINDOW_NO_SCROLLBAR))
    {
        struct nk_vec2 menuSize = nk_vec2(125, 200);

        nk_layout_row_static(ctx, TOP_TOOLBAR_HEIGHT, 50, 2);

        if (nk_menu_begin_label(ctx, "File", NK_TEXT_LEFT, menuSize)) 
        {
            nk_layout_row_dynamic(ctx, 25, 1);
            if (nk_menu_item_label(ctx, "Open model", NK_TEXT_LEFT)) 
            {
                if(!fileBrowser)
                    fileBrowser = cutilFileBrowserInit(".", "obj");

                if(!renderFileBrowser)
                    renderFileBrowser = 1;
            }
            nk_menu_end(ctx);
        }
        
        /*
        if (nk_menu_begin_label(ctx, "Help", NK_TEXT_LEFT, menuSize)) 
        {
            nk_layout_row_dynamic(ctx, 25, 1);
            if (nk_menu_item_label(ctx, "About", NK_TEXT_LEFT)) 
            {

            }
            nk_menu_end(ctx);
        }
        */
    }
    nk_end(ctx);

    if (nk_begin(ctx, "top-fps", nk_rect(0, TOP_TOOLBAR_HEIGHT, width, TOP_TOOLBAR_HEIGHT), NK_WINDOW_NO_SCROLLBAR))
    {
        nk_layout_row_static(ctx, TOP_TOOLBAR_HEIGHT, width, 1);
        sprintf(fpsBuffer, "FPS: %d", context->framesPerSecond);
        nk_label(ctx, fpsBuffer, NK_TEXT_LEFT);
    }
    nk_end(ctx);
}

void s3vUIRenderFilebrowser()
{
    int selected = 0;
    if (nk_begin(ctx, "files", nk_rect(width / 4, height / 4, width / 2, height / 2), 
        NK_WINDOW_TITLE | NK_WINDOW_NO_SCROLLBAR))
    {
        nk_layout_row_dynamic(ctx, height / 2 - 70, 1);
        if (nk_group_begin(ctx, "column", NK_WINDOW_BORDER)) {

            for(int i = 0; i < fileBrowser->directoryContentsSize; i++)
            {
                CUTILFilesystemItem* item = &fileBrowser->directoryContents[i];
                
                nk_layout_row_begin(ctx, NK_DYNAMIC, 15, 2);

                nk_layout_row_push(ctx, 0.05f);
                if(item->isDirectory) 
                    nk_label(ctx, "[d]", NK_TEXT_LEFT);
                else
                    nk_label(ctx, "[f]", NK_TEXT_LEFT);

                nk_layout_row_push(ctx, 0.95f);
                if(nk_selectable_label(ctx, item->name, NK_TEXT_LEFT, &selected)) 
                {
                    char* file = cutilFileBrowserSelectItem(fileBrowser, i);
                    if(file) 
                    {
                        renderFileBrowser = 0;
                        S3VMesh* mesh = s3vMeshCreate();
                        s3vMeshCreateFromFile(file, mesh);
                        s3vRendererRenderMesh(mesh);
                    }
                }

                nk_layout_row_end(ctx);
            }

            nk_group_end(ctx);
        }

        nk_layout_row_static(ctx, 30, 55, 1);

        if (nk_button_label(ctx, "cancel")) 
        {
            renderFileBrowser = 0;
        }

    }
    nk_end(ctx);
}
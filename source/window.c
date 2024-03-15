#include "s3v/window.h"
#include "s3v/ui.h"
#include "s3v/mouse.h"

static int frameCount = 0;
static double previousTime = 0;
GLFWwindow* s3vWindow = NULL;

static void error_callback(int error, const char* description)
{
    printf("Error: %d: %s\n", error, description);
}

int s3vWindowOpen(int width, int height, const char* title) 
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        s3vSetErrorMessage("");
        return S3V_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    s3vWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!s3vWindow)
    {
        glfwTerminate();
        s3vSetErrorMessage("");
        return S3V_FAILURE;
    }

    glfwMakeContextCurrent(s3vWindow);
    gladLoadGL();
    glfwSwapInterval(1);

    const GLubyte* renderer = glGetString(GL_RENDERER);     // get renderer string
    const GLubyte* version = glGetString(GL_VERSION);       // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    s3vUIInit();
    s3vMouseInit();

    return S3V_SUCCESS;
}

int s3vWindowShouldClose() 
{
    if(!s3vWindow || glfwWindowShouldClose(s3vWindow) == GLFW_TRUE) return S3V_TRUE;
    return S3V_FALSE;
}

void s3vWindowClose() 
{
    if(!s3vWindow) return;
    //s3vUIFinish();
    glfwDestroyWindow(s3vWindow);
}

void s3vWindowUpdateFPS(S3VContext* context)
{
    double currentTime = glfwGetTime();
    frameCount++;
    if (currentTime - previousTime >= 1.0) {
        context->framesPerSecond = frameCount;
        frameCount = 0;
        previousTime = currentTime;
    }
}

void s3vWindowRender(S3VContext* context)
{
    s3vUIRender(context);
    s3vWindowUpdateFPS(context);
}

void s3vWindowUpdate(S3VContext* context) 
{
    glfwSwapBuffers(s3vWindow);
    glfwPollEvents();

    glfwGetWindowSize(s3vWindow, &context->windowWidth, &context->windowHeight);
    
    context->mouseButton = s3vMouseGetPressKey();
    s3vMouseGetHoldDelta(&context->mouseDeltaX, &context->mouseDeltaY);
    context->renderingOptions.drawWireframe = 1;
}
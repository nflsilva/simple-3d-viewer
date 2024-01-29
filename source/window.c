#include "s3v/window.h"
#include "s3v/ui.h"

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
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

    s3vUIInit(s3vWindow);

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
    s3vUIFinish();
    glfwDestroyWindow(s3vWindow);
}

void s3vWindowUpdate() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    glfwPollEvents();

    s3vUIUpdate();

    glfwSwapBuffers(s3vWindow);
}
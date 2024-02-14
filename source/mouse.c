#include "s3v/mouse.h"

extern GLFWwindow* s3vWindow;
static int keyPressed;
static double pressX, pressY;
static float deltaX, deltaY;

static void mouse_callback(GLFWwindow* window, double xpos, double ypos) 
{
    if(keyPressed)
    {
        if(pressX == -1 && pressY == -1) 
        {
            pressX = xpos;
            pressY = ypos;
        }

        deltaX = pressX - xpos;
        deltaY = pressY - ypos;
    }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) 
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        keyPressed = 1;
        pressX = -1;
        pressY = -1;
    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        keyPressed = 0;
        deltaX = 0;
        deltaY = 0;
    }

}

int s3vMouseInit()
{
    glfwSetMouseButtonCallback(s3vWindow, mouse_button_callback);
    glfwSetCursorPosCallback(s3vWindow, mouse_callback);
    keyPressed = 0;
}

int s3vMouseGetPressKey()
{
    return keyPressed;
}

void s3vMouseGetHoldDelta(float* dX, float* dY)
{
    *dX = (float)deltaX;
    *dY = (float)deltaY;
}
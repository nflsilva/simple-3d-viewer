#include "s3v/keyboard.h"

extern GLFWwindow* s3vWindow;
static int currentKeyboardStateIndex = 0;
static int keyboardStates[2][25];

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if(window != s3vWindow) return;

    switch (action)
    {
        case GLFW_PRESS:
            keyboardStates[currentKeyboardStateIndex][key - S3V_KEY_A] = S3V_TRUE;
            break;
        case GLFW_RELEASE:
            keyboardStates[currentKeyboardStateIndex][key - S3V_KEY_A] = S3V_FALSE;
            break;
        default:
            break;
    }
}

int s3vStartKeyboard() 
{
    if(!s3vWindow) return S3V_FAILURE;
    glfwSetKeyCallback(s3vWindow, key_callback);
    return S3V_SUCCESS;
}

int s3vKeyIsPressed(int key) 
{
    return keyboardStates[currentKeyboardStateIndex][key - S3V_KEY_A];
}

int s3vKeyIsReleased(int key) 
{
    int lastKeyboarStateIndex = (currentKeyboardStateIndex + 1) % 2;
    int lastKeyState = keyboardStates[lastKeyboarStateIndex][key - S3V_KEY_A];
    int currentKeyState = keyboardStates[currentKeyboardStateIndex][key];
    return lastKeyState && !currentKeyState;
}

int s3vKeyIsHold(int key) 
{
    int lastKeyboarStateIndex = (currentKeyboardStateIndex + 1) % 2;
    int lastKeyState = keyboardStates[lastKeyboarStateIndex][key - S3V_KEY_A];
    int currentKeyState = keyboardStates[currentKeyboardStateIndex][key - S3V_KEY_A];
    return lastKeyState && currentKeyState;
}

void s3vUpdateKeyboard() 
{
    currentKeyboardStateIndex++;
    currentKeyboardStateIndex = currentKeyboardStateIndex % 2;
    memset(keyboardStates[currentKeyboardStateIndex], S3V_FALSE, sizeof(keyboardStates[currentKeyboardStateIndex]));
}

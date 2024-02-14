#ifndef _S3V_MOUSE_H
#define _S3V_MOUSE_H

#include <GLFW/glfw3.h>

#include "s3v/s3v.h"

/*!
 *  Starts scanning for key inputs from mouse
 * @returns `S3V_SUCCESS` if successfull. `S3V_FAILURE` if an error occurred
 * or the window is not opened.
 */
int s3vMouseInit();

int s3vMouseGetPressKey();

/*!
 * Checks if a given key was pressed.
 * @param key The key to check for press.
 * @returns `S3V_TRUE` if key was pressed. `S3V_FALSE` otherwise.
 */
void s3vMouseGetHoldDelta(float* deltaX, float* deltaY);

#endif

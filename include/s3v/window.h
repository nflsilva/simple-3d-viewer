#ifndef _SMT_WINDOW_H
#define _SMT_WINDOW_H

#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "s3v/s3v.h"

/*!
 *  Opens the application window with a valid OpenGL context.
 * @param width The window width to set.
 * @param height The window height to set.
 * @param title The window height to set.
 * @returns `SMT_SUCCESS` if successfull. `SMT_FAILURE` if an error occurred
 * or the window is already opened.
 */
int s3vWindowOpen(int width, int height, const char* title);

/*!
 *  Indicates if the applicatin window will close.
 * @returns `SMT_TRUE` if the window will close. `SMT_FALSE` otherwise.
 */
int s3vWindowShouldClose();

/*!
 *  Destroys window context.
 */
void s3vWindowClose();

/*!
 *  Updates window context.
 */
void s3vWindowUpdate();

#endif
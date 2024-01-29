#ifndef _S3V_UI_H
#define _S3V_UI_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*!
 * Initializes the UI system.
 * @param window A pointer to the current GLFWwindow.
 */
void s3vUIInit(GLFWwindow* window);

/*!
 * Updates and redraws all the UI components on the current window.
 */
void s3vUIUpdate();

/*!
 * Shutsdown and cleansup the current UI system
 */
void s3vUIFinish();

/*!
 * Renders a toolbar on the top of the screen
 */
void s3vUIRenderToolbar();

/*!
 * Renders a file browser popup
 */
void s3vUIRenderFilebrowser();

#endif
#ifndef _S3V_UI_H
#define _S3V_UI_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "s3v/context.h"

/*!
 * Initializes the UI system.
 */
void s3vUIInit();

/*!
 * Updates and redraws all the UI components on the current window.
 */
void s3vUIRender(S3VContext* context);

/*!
 * Shutsdown and cleansup the current UI system
 */
void s3vUIFinish();

/*!
 * Renders a toolbar on the top of the screen
 */
void s3vUIRenderTopToolbar();

/*!
 * Renders a toolbar on the left of the screen
 */
void s3vUIRenderSideToolbar();

/*!
 * Renders a file browser popup
 */
void s3vUIRenderFilebrowser();

#endif
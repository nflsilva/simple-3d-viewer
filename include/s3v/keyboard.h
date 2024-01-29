#ifndef _S3V_KEYBOARD_H
#define _S3V_KEYBOARD_H

#include <GLFW/glfw3.h>

#include "s3v/s3v.h"

#define S3V_KEY_0 48
#define S3V_KEY_1 49
#define S3V_KEY_2 50
#define S3V_KEY_3 51
#define S3V_KEY_4 52
#define S3V_KEY_5 53
#define S3V_KEY_6 54
#define S3V_KEY_7 55
#define S3V_KEY_8 56
#define S3V_KEY_9 57

#define S3V_KEY_A 65
#define S3V_KEY_B 66
#define S3V_KEY_C 67
#define S3V_KEY_D 68
#define S3V_KEY_E 69
#define S3V_KEY_F 70
#define S3V_KEY_G 71
#define S3V_KEY_H 72
#define S3V_KEY_I 73
#define S3V_KEY_J 74
#define S3V_KEY_K 75
#define S3V_KEY_L 76
#define S3V_KEY_M 77
#define S3V_KEY_N 78
#define S3V_KEY_O 79
#define S3V_KEY_P 80
#define S3V_KEY_Q 81
#define S3V_KEY_R 82
#define S3V_KEY_S 83
#define S3V_KEY_T 84
#define S3V_KEY_U 85
#define S3V_KEY_V 86
#define S3V_KEY_W 87
#define S3V_KEY_X 88
#define S3V_KEY_Y 89
#define S3V_KEY_Z 90

#define S3V_KEY_RIGHT 262
#define S3V_KEY_LEFT 263
#define S3V_KEY_DOWN 264
#define S3V_KEY_UP 265

/*!
 *  Starts scanning for key inputs from keyboard
 * @returns `S3V_SUCCESS` if successfull. `S3V_FAILURE` if an error occurred
 * or the window is not opened.
 */
int s3vStartKeyboard();

/*!
 * Checks if a given key was pressed.
 * @param key The key to check for press.
 * @returns `S3V_TRUE` if key was pressed. `S3V_FALSE` otherwise.
 */
int s3vKeyIsPressed(int key);

/*!
 * Checks if a given key was released.
 * @param key The key to check for release.
 * @returns `S3V_FALSE` if key was release. `S3V_FALSE` otherwise.
 */
int s3vKeyIsReleased(int key);

/*!
 * Checks if a given key is being hold.
 * @param key The key to check for hold.
 * @returns `S3V_FALSE` if key is being hold. `S3V_FALSE` otherwise.
 */
int s3vKeyIsHold(int key);

/*!
 *  Updates keyboard context.
 */
void s3vUpdateKeyboard();

#endif
#ifndef _S3V_H
#define _S3V_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 *  Semantic sugar for the number `1`.
 */
#define S3V_TRUE 1
/*
 *  Semantic sugar for the number `0`.
 */
#define S3V_FALSE 0
/*
 *  Semantic sugar for the number `1`.
 */
#define S3V_SUCCESS 1
/*
 *  Semantic sugar for the number `0`.
 */
#define S3V_FAILURE 0

/*!
 * Gets the last error message from S3V.
 * @param message The error message to set.
 */
char* s3vGetErrorMessage();

/*!
 * Sets the last error message for S3V.
 * @param message The error message to set.
 */
void s3vSetErrorMessage(const char* message);

#endif
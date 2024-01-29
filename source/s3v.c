#include "s3v/s3v.h"

static int s3vErrorMessageSize = 0;
char *s3vErrorMessage = NULL;

char* s3vGetErrorMessage() 
{
    return s3vErrorMessage;
}

void s3vSetErrorMessage(const char* message) 
{
    int newMessageSize = strlen(message);
    if(newMessageSize >= s3vErrorMessageSize) 
    {
        if(s3vErrorMessageSize != 0) 
            free(s3vErrorMessage);

        s3vErrorMessage = (char*)malloc(sizeof(char) * newMessageSize + 1);
    }
    s3vErrorMessageSize = newMessageSize;
    strcpy(s3vErrorMessage, message);
    printf("s3v_error: %s\n", s3vErrorMessage);
}
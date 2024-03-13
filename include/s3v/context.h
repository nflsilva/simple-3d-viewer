#ifndef _S3V_UPDATE_CONTEXT_H
#define _S3V_UPDATE_CONTEXT_H

typedef struct S3VContext {
    int windowWidth, windowHeight;
    int mouseX, mouseY, mouseButton;
    float mouseDeltaX, mouseDeltaY; 
    int framesPerSecond;
} S3VContext;

#endif
#ifndef _S3V_UPDATE_CONTEXT_H
#define _S3V_UPDATE_CONTEXT_H

typedef struct S3VRenderingOptions {
    int drawWireframe;

} S3VRenderingOptions;

typedef struct S3VContext {
    int windowWidth, windowHeight;
    int mouseX, mouseY, mouseButton;
    float mouseDeltaX, mouseDeltaY; 
    int framesPerSecond;
    S3VRenderingOptions renderingOptions;
} S3VContext;

#endif
#ifndef _S3V_RENDERER_H
#define _S3V_RENDERER_H

#include <assert.h>

#include "cvec/mat4.h"
#include "cutil/math.h"
#include "s3v/context.h"
#include "s3v/mesh.h"
#include "s3v/shader.h"

/*!
 * Represents all the components of the renderer.
 * @param shader the OpenGL program id number for this shader.
 * @param mesh the mesh to render.
 * @param pvmMatrix the projection-view-model combined matrix.
 * @param projectionMatrix the projection matrix.
 * @param viewMatrix the view matrix (camera matrix).
 */
typedef struct S3VRenderer {
    S3VShader* shader;
    S3VMesh* mesh;
    CVECMat4F* pvmMatrix;
    CVECMat4F* projectionMatrix;
    CVECMat4F* modelMatrix;
    CVECMat4F* viewMatrix;
} S3VRenderer;

/*!
 * Inits the rendering context. Allocs all the necessary matrices and properties for the
 * renderer.
 */
void s3vRendererInit();

/*!
 * Destroys and frees the rendering context.
 */
void s3vRendererDestroy();

/*!
 * Triggers the rendering process
 * @param context the context state for the current frame
 */
void s3vRendererRender(S3VContext* context);

/*!
 * Sets the mesh to render
 * @param mesh the context state for the current frame
 */
void s3vRendererRenderMesh(S3VMesh* mesh);

#endif
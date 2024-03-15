#ifndef _S3V_MESH_H
#define _S3V_MESH_H

#include <assert.h>
#include <glad/glad.h>
#include <stdlib.h>
#include <string.h>

#include "s3v/s3v.h"
#include "cutil/list.h"
#include "cutil/filebrowser.h"
#include "cutil/vector.h"
#include "cutil/hash_table.h"

#define S3V_BATCH_MAX_ATTRIBUTES 20

/*!
 * Represents a single mesh vertex.
 * @param position the vertex 3D position
 * @param normal the vertex 3D normal
 * @param uv the vertex texture coordinates
 */
typedef struct S3VMeshVertex {
    float position[3];
    float normal[3];
    float uv[2];
} S3VMeshVertex;

/*!
 * Represents a mesh.
 * @param glVAO the mesh OpenGL Vertex Array Object ID
 * @param glVBO the mesh OpenGL Vertex Buffer Object ID
 * @param glEBO the mesh OpenGL Element Buffer Object ID
 * @param nElements the number of elements to draw
 * @param maxElement the max number of elements in this mesh
 * @param maxDistance the maximum position value on all axis
 */
typedef struct S3VMesh {
    // mesh has a simple VAO and VBO, for now
    GLuint glVAO;
    GLuint glVBO;
    GLuint glEBO;
    unsigned int nElements, maxElements;
    float maxDistance;
} S3VMesh;

/*!
 * Creates a mesh in ram
 * @return a pointer to the new mesh
 */
S3VMesh* s3vMeshCreate();

/*!
 * Initializes and buffers a mesh in vram.
 * @param mesh a pointer to the mesh to initialize
 * @param vertices a pointer to an array of mesh vertices
 * @param nVertices the number of vertices
 * @param indices a pointer to an array of mesh elements
 * @param nIndices the number of mesh elements
 */
void s3vMeshInit(S3VMesh* mesh, S3VMeshVertex* vertices, int nVertices, unsigned int* indices, int nIndices);

/*!
 * Releases a mesh from ram and vram
 * @param mesh a pointer to the mesh to destroy
 */
void s3vMeshDestroy(S3VMesh* mesh);

/*!
 * Binds a mesh for rendering
 * @param mesh a pointer to the mesh to bind
 */
void s3vMeshBind(S3VMesh* mesh);

/*!
 * Binds all meshes
 */
void s3vMeshUnbind();

/*!
 * Loads and initialize a mesh from an .obj file
 * @param directoryPath path to the file to load
 * @param mesh a pointer to the mesh to initialize
 */
void s3vMeshCreateFromFile(const char* directoryPath, S3VMesh* mesh);

#endif
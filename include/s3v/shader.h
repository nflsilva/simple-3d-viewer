#ifndef _S3V_SHADER_H
#define _S3V_SHADER_H

#include <glad/glad.h>

#include "cutil/hashTable.h"
#include "cutil/list.h"
#include "cutil/filebrowser.h"
#include "s3v/s3v.h"

/*!
 * Represents an OpenGL shader context.
 * @param programId The OpenGL program id number for this shader.
 * @param shaderList A list of shader codes which compose this shader.
 * @param uniformLocations The map which stores the location for each uniform.
 */
typedef struct S3VShader {
    int programId;
    CUTILList* shaderList;
    CUTILHashTable* uniformLocations;
} S3VShader;

/*!
 * Creates a new shader program to run on the GPU.
 * @param vertexCode The code for the vertex shader program.
 * @param fragmentCode The code for the fragment shader program.
 * @returns A pointer to the newly created shader. `NULL` if an error occurred.
 */
S3VShader* s3vShaderCreate(const char** vertexCode, const char** fragmentCode);

/*!
 * Destroys and cleans up a given shader.
 * @param shader The shader to destroy.
 */
void s3vShaderDestroy(S3VShader* shader);

/*!
 * Binds a given shader to be used.
 * @param shader The shader to bind.
 */
void s3vShaderBind(S3VShader* shader);

/*!
 * Unbinds all shaders
 */
void s3vShaderUnbind();

/*!
 * Links the program on the shader
 * @param shader The shader to link.
 * @return 'S3V_SUCCESS' if everything when well. 'S3V_FAILURE' otherwise.
 */
int s3vShaderLinkProgram(S3VShader* shader);

/*!
 * Binds a shader variable to a specific attribute
 * @param shader The shader
 * @param attribute The position to bind the variable
 * @param variableName The shader variable name
 */
void s3vShaderBindAttribute(S3VShader* shader, int attribute, const char* variableName);

/*!
 * Creates and stores a shader uniform location
 * @param shader The shader
 * @param name The uniform name
 * @return 'S3V_SUCCESS' if everything when well. 'S3V_FAILURE' otherwise. 
 */
int s3vShaderAddUniform(S3VShader* shader, const char* name);

/*!
 * Sets the value for a specific shader uniform of type `int`
 * @param shader The shader
 * @param name The uniform name
 * @param value The value to set
 * @return 'S3V_SUCCESS' if everything when well. 'S3V_FAILURE' otherwise. 
 */
int s3vShaderSetUniformI(S3VShader* shader, const char* name, int value);

/*!
 * Sets the value for a specific shader uniform of type ´float´
 * @param shader The shader
 * @param name The uniform name
 * @param value The value to set
 * @return 'S3V_SUCCESS' if everything when well. 'S3V_FAILURE' otherwise. 
 */
int s3vShaderSetUniformF(S3VShader* shader, const char* name, float value);

/*!
 * Sets the value for a specific shader uniform of type `vec3`
 * @param shader The shader
 * @param name The uniform name
 * @param value A pointer to the list of values to set
 * @return 'S3V_SUCCESS' if everything when well. 'S3V_FAILURE' otherwise. 
 */
int s3vShaderSetUniformVec3F(S3VShader* shader, const char* name, float* values);

/*!
 * Sets the value for a specific shader uniform of type `vec4`
 * @param shader The shader
 * @param name The uniform name
 * @param value A pointer to the list of values to set
 * @return 'S3V_SUCCESS' if everything when well. 'S3V_FAILURE' otherwise. 
 */
int s3vShaderSetUniformVec4F(S3VShader* shader, const char* name, float* values);

/*!
 * Sets the value for a specific shader uniform of type `mat4`
 * @param shader The shader
 * @param name The uniform name
 * @param value A pointer to the list of values to set
 * @return 'S3V_SUCCESS' if everything when well. 'S3V_FAILURE' otherwise. 
 */
int s3vShaderSetUniformMat4F(S3VShader* shader, const char* name, float* values);

/*!
 * Creates a shader for the different available shapes.
 * @returns A pointer to the newly created shader. `NULL` if an error occurred.
 */
S3VShader* s3vShaderCreateDefaultShader();

#endif
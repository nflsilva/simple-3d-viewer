#include "s3v/shader.h"

void s3vShaderGetShaderInfoLog(int glShader)
{
    GLsizei logLength = 0;
    GLchar message[1024];
    glGetShaderInfoLog(glShader, 1024, &logLength, message);
    s3vSetErrorMessage(message);
}

int s3vShaderAddCode(S3VShader* shader, const char** code, int type)
{
    if(!shader || !shader->shaderList) return S3V_FAILURE;

    int glShader = glCreateShader(type);
    if(!glShader) return S3V_FAILURE;

    glShaderSource(glShader, 1, code, NULL);
    glCompileShader(glShader);

    GLint success;
    glGetShaderiv(glShader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        s3vShaderGetShaderInfoLog(glShader);
        return S3V_FAILURE;
    }
    int* glShaderPtr = (int*)malloc(sizeof(int));
    *glShaderPtr = glShader;

    glAttachShader(shader->programId, glShader);
    cutilListPushElement(shader->shaderList, glShaderPtr);
    return S3V_SUCCESS;
}

S3VShader* s3vShaderCreate(const char** vertexCode, const char** fragmentCode) 
{
    int programId = glCreateProgram();
    if(!programId)
    {
        s3vSetErrorMessage("Program creation failed");
        return NULL;
    }

    S3VShader* shader = (S3VShader*)malloc(sizeof(S3VShader));
    shader->programId = programId;
    shader->shaderList = cutilListCreate();
    shader->uniformLocations = cutilHashTableCreate();

    if(!s3vShaderAddCode(shader, vertexCode, GL_VERTEX_SHADER)) return NULL;
    if(!s3vShaderAddCode(shader, fragmentCode, GL_FRAGMENT_SHADER)) return NULL;
    if(!s3vShaderLinkProgram(shader)) return NULL;

    return shader;
}

void s3vShaderDestroy(S3VShader* shader)
{
    if(!shader || !shader->shaderList || !shader->uniformLocations) return;

    s3vShaderUnbind(shader);

    for(int i = 0; i < shader->shaderList->size; i++)
    {
        int glShader = *(int*)cutilListPopElement(shader->shaderList);
        glDetachShader(shader->programId, glShader);
        glDeleteShader(glShader);
    }
    glDeleteProgram(shader->programId);
    cutilListDestroy(shader->shaderList, S3V_FALSE);
    cutilHashTableDestroy(shader->uniformLocations, S3V_FALSE);
    free(shader);
}

void s3vShaderBind(S3VShader* shader)
{
    if(!shader) return;
    glUseProgram(shader->programId);
}

void s3vShaderUnbind()
{
    glUseProgram(0);
}

int s3vShaderLinkProgram(S3VShader* shader)
{
    GLint success;

    glLinkProgram(shader->programId);
    glGetProgramiv(shader->programId, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        //s3vShaderGetProgramInfoLog(shader);
        return S3V_FAILURE;
    }

    glValidateProgram(shader->programId);
    glGetProgramiv(shader->programId, GL_VALIDATE_STATUS, &success);
    if (success != GL_TRUE)
    {
        //s3vShaderGetProgramInfoLog(shader);
        return S3V_FAILURE;
    }
    return S3V_SUCCESS;
}

void s3vShaderBindAttribute(S3VShader* shader, int attribute, const char* variableName)
{
    glBindAttribLocation(shader->programId, attribute, variableName);
}

int s3vShaderAddUniform(S3VShader* shader, const char* name)
{
    GLuint location = glGetUniformLocation(shader->programId, name);
    if(location == GL_INVALID_VALUE || location == GL_INVALID_OPERATION || location == GL_INVALID_OPERATION)
    {
        //s3vShaderGetProgramInfoLog(shader);
        return S3V_FAILURE;
    }
    cutilHashTableAddElement(shader->uniformLocations, name, &location);
    return S3V_SUCCESS;
}

int s3vShaderSetUniformI(S3VShader* shader, const char* name, int value)
{
    GLuint location = *(GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        s3vSetErrorMessage("Location not found");
        return S3V_FAILURE;
    }
	glUniform1i(location, value);
    return S3V_SUCCESS;
}

int s3vShaderSetUniformF(S3VShader* shader, const char* name, float value)
{
    GLuint location = *(GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        s3vSetErrorMessage("Location not found");
        return S3V_FAILURE;
    }
	glUniform1f(location, value);
    return S3V_SUCCESS;
}

int s3vShaderSetUniformVec3F(S3VShader* shader, const char* name, float* values)
{
    GLuint location = *(GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        s3vSetErrorMessage("Location not found");
        return S3V_FAILURE;
    }
	glUniform3f(location, values[0], values[1], values[2]);
    return S3V_SUCCESS;
}

int s3vShaderSetUniformVec4F(S3VShader* shader, const char* name, float* values)
{
    GLuint location = *(GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        s3vSetErrorMessage("Location not found");
        return S3V_FAILURE;
    }
	glUniform4f(location, values[0], values[1], values[2], values[3]);
    return S3V_SUCCESS;
}

int s3vShaderSetUniformMat4F(S3VShader* shader, const char* name, float* values)
{
    GLuint location = *(GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        s3vSetErrorMessage("Location not found");
        return S3V_FAILURE;
    }
	glUniformMatrix4fv(location, 1, GL_FALSE, values);
    return S3V_SUCCESS;
}

S3VShader* s3vShaderCreateDefaultShader()
{
    const char* vertexShaderCode = cutilFileBrowserLoadFile("../assets/shader/vertex.glsl");
    if(!vertexShaderCode) return NULL;
    const char* fragmentShaderCode = cutilFileBrowserLoadFile("../assets/shader/fragment.glsl");
    if(!fragmentShaderCode) return NULL;
    
    S3VShader* shader = s3vShaderCreate(&vertexShaderCode, &fragmentShaderCode);
    if(!shader) return NULL;

    s3vShaderAddUniform(shader, "uni_modelMatrix");
    s3vShaderAddUniform(shader, "uni_viewMatrix");
    s3vShaderAddUniform(shader, "uni_modelMatrix");

    free((char*)vertexShaderCode);
    free((char*)fragmentShaderCode);

    return shader;
}

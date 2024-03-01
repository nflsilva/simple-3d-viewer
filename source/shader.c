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
    assert(shader);
    assert(shader->shaderList);
    assert(shader->uniformLocations);

    s3vShaderUnbind(shader);
    glDeleteProgram(shader->programId);

    int* glShaderPtr = (int*)cutilListPopElement(shader->shaderList);
    while(glShaderPtr != NULL)
    {
        int glShader = *glShaderPtr;
        glDetachShader(shader->programId, glShader);
        glDeleteShader(glShader);

        free(glShaderPtr);
        glShaderPtr = (int*)cutilListPopElement(shader->shaderList);
    }
    cutilListDestroy(shader->shaderList);

    for(int i = 0; i < _CUTIL_TABLE_SIZE; i++)
    {
        CUTILHashTableBucket* bucket = &shader->uniformLocations->buckets[i];
        if(!bucket->chain) continue;

        CUTILListNode* node = bucket->chain->head;
        while(node != NULL)
        {
            CUTILHashTableBucketChainNode* cn = (CUTILHashTableBucketChainNode*)node->data;
            node = node->next;
            free(cn->data);
        }
    }
    cutilHashTableDestroy(shader->uniformLocations);
    
    free(shader);
}

void s3vShaderBind(S3VShader* shader)
{
    assert(shader);
    glUseProgram(shader->programId);
}

void s3vShaderUnbind()
{
    glUseProgram(0);
}

int s3vShaderLinkProgram(S3VShader* shader)
{
    assert(shader);
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
    assert(shader);
    glBindAttribLocation(shader->programId, attribute, variableName);
}

int s3vShaderAddUniform(S3VShader* shader, const char* name)
{
    assert(shader);
    GLuint location = glGetUniformLocation(shader->programId, name);
    if(location == GL_INVALID_VALUE || location == GL_INVALID_OPERATION || location == GL_INVALID_OPERATION)
    {
        //s3vShaderGetProgramInfoLog(shader);
        return S3V_FAILURE;
    }
    GLuint* heapLocation = (GLuint*)malloc(sizeof(GLuint));
    *heapLocation = location; 
    cutilHashTableAddElement(shader->uniformLocations, name, ((GLuint*) heapLocation));
    return S3V_SUCCESS;
}

int s3vShaderSetUniformI(S3VShader* shader, const char* name, int value)
{
    assert(shader);
    GLuint* location = (GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        s3vSetErrorMessage("Location not found");
        return S3V_FAILURE;
    }
	glUniform1i(*location, value);
    return S3V_SUCCESS;
}

int s3vShaderSetUniformF(S3VShader* shader, const char* name, float value)
{
    assert(shader);
    GLuint* location = (GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        s3vSetErrorMessage("Location not found");
        return S3V_FAILURE;
    }
	glUniform1f(*location, value);
    return S3V_SUCCESS;
}

int s3vShaderSetUniformVec3F(S3VShader* shader, const char* name, float values[3])
{
    assert(shader);
    GLuint* location = (GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        s3vSetErrorMessage("Location not found");
        return S3V_FAILURE;
    }
	glUniform3f(*location, values[0], values[1], values[2]);
    return S3V_SUCCESS;
}

int s3vShaderSetUniformVec4F(S3VShader* shader, const char* name, float values[4])
{
    assert(shader);
    GLuint* location = (GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        s3vSetErrorMessage("Location not found");
        return S3V_FAILURE;
    }
	glUniform4f(*location, values[0], values[1], values[2], values[3]);
    return S3V_SUCCESS;
}

int s3vShaderSetUniformMat4F(S3VShader* shader, const char* name, float values[4][4])
{
    assert(shader);
    GLuint* location = (GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        s3vSetErrorMessage("Location not found");
        return S3V_FAILURE;
    }
	glUniformMatrix4fv(*location, 1, GL_FALSE, &values[0][0]);
    return S3V_SUCCESS;
}

S3VShader* s3vShaderCreateDefaultShader()
{
    const char* vertexShaderCode = cutilFileBrowserLoadFile("/mnt/storage/w0/projects/simple-3d-viewer/assets/shader/vertex.glsl");
    if(!vertexShaderCode) return NULL;
    const char* fragmentShaderCode = cutilFileBrowserLoadFile("/mnt/storage/w0/projects/simple-3d-viewer/assets/shader/fragment.glsl");
    if(!fragmentShaderCode) return NULL;
    
    S3VShader* shader = s3vShaderCreate(&vertexShaderCode, &fragmentShaderCode);
    if(!shader) return NULL;

    s3vShaderAddUniform(shader, "uni_pvmMatrix");
    s3vShaderAddUniform(shader, "uni_projectionMatrix");
    s3vShaderAddUniform(shader, "uni_viewMatrix");
    s3vShaderAddUniform(shader, "uni_modelMatrix");

    free((char*)vertexShaderCode);
    free((char*)fragmentShaderCode);

    return shader;
}

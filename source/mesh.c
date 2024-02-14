#include "s3v/mesh.h"

void s3vMeshSetIndexAttribute(S3VMesh* mesh, unsigned int count, unsigned int* buffer)
{
    assert(mesh);
    assert(mesh->indexAttribute.glVBO == 0);

    S3VMeshAttribute* attr = &mesh->indexAttribute;
    attr->count = count;
    attr->sizeInBytes = count * sizeof(GL_UNSIGNED_INT);
    attr->data = buffer;

    glBindVertexArray(mesh->glVAO);

    glGenBuffers(1, &attr->glVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, attr->glVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, attr->sizeInBytes, buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void s3vMeshAttributeAdd(S3VMesh* mesh, unsigned int nComponents, unsigned int count, int type, void* buffer)
{
    assert(mesh);

    S3VMeshAttribute* attr = &mesh->attributes[mesh->nAttributes];
    attr->count = count;
    attr->sizeInBytes = sizeof(type) * nComponents * count;
    attr->data = buffer;

    glBindVertexArray(mesh->glVAO);

    glGenBuffers(1, &attr->glVBO);
    glBindBuffer(GL_ARRAY_BUFFER, attr->glVBO);
    glBufferData(GL_ARRAY_BUFFER, attr->sizeInBytes, buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(mesh->nAttributes, nComponents, type, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    mesh->nAttributes++;
}

void s3vMeshAttributeDestroy(S3VMeshAttribute* attribute)
{
    assert(attribute);
    glDeleteBuffers(1, &attribute->glVBO);
}

S3VMesh* s3vMeshCreate()
{
    S3VMesh* mesh = (S3VMesh*)malloc(sizeof(S3VMesh));
    mesh->glVAO = 0;
    mesh->nAttributes = 0;
    mesh->indexAttribute.glVBO = 0;
    mesh->indexAttribute.count = 0;
    glGenVertexArrays(1, &mesh->glVAO);
    return mesh;
}

void s3vMeshDestroy(S3VMesh* mesh)
{
    assert(mesh);
    glDeleteVertexArrays(1, &mesh->glVAO);

    for(unsigned int i = 0; i < mesh->nAttributes; i++)
        s3vMeshAttributeDestroy(&mesh->attributes[i]);

    s3vMeshAttributeDestroy(&mesh->indexAttribute);
    free(mesh);
}

void s3vMeshBind(S3VMesh* mesh)
{
    assert(mesh);

    glBindVertexArray(mesh->glVAO);
    for(unsigned int i = 0; i < mesh->nAttributes; i++) 
    {
        glEnableVertexAttribArray(i);

        //S3VMeshAttribute* attr = &mesh->attributes[i];
        //glBindBuffer(GL_ARRAY_BUFFER, attr->glVBO);
        //glBufferSubData(GL_ARRAY_BUFFER, 0, attr->sizeInBytes, attr->data);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexAttribute.glVBO);
    //S3VMeshAttribute* iAttr = &mesh->indexAttribute;
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iAttr->glVBO);
    //glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, iAttr->sizeInBytes, iAttr->data);
}

void s3vMeshUnbind()
{
    glBindVertexArray(0);
}

void s3vMeshCreateFromFile(const char* directoryPath, S3VMesh* mesh)
{
    assert(mesh);
    
    FILE *file = fopen(directoryPath, "r");
    
    // check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // buffer to store each line
    char line[100];

    int nVertices = 0;
    int maxVertices = 1024 * 3;
    float* vertices = (float*)malloc(sizeof(float) * maxVertices);

    int nNormals = 0;
    int maxNormals = 1024 * 3;
    float* normals = (float*)malloc(sizeof(float) * maxNormals);

    int nIndices = 0;
    int maxIndices = 1024 * 3;
    unsigned int* indices = (unsigned int*)malloc(sizeof(unsigned int) * maxIndices);

    // read the file line by line
    while (fgets(line, sizeof(line), file) != NULL) 
    {
        if(line[0] == 'v' && line[1] == 'n')
        {
            sscanf(line, "vn %f %f %f", 
                &normals[nNormals], 
                &normals[nNormals + 1], 
                &normals[nNormals + 2]);
            nNormals += 3;
            if(nNormals == maxNormals)
            {
                maxNormals *= 2;
                normals = (float*)realloc(normals, sizeof(float) * maxNormals * 3);
            }
        }
        else if(line[0] == 'v')
        {
            sscanf(line, "v %f %f %f", 
                &vertices[nVertices], 
                &vertices[nVertices + 1], 
                &vertices[nVertices + 2]);
            nVertices += 3;
            if(nVertices == maxVertices)
            {
                maxVertices *= 2;
                vertices = (float*)realloc(vertices, sizeof(float) * maxVertices * 3);
            }

        }
        else if(line[0] == 'f')
        {
            sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", 
                &indices[nIndices], 
                &indices[nIndices + 1], 
                &indices[nIndices + 2]);

            for(int i = 0; i < 3; i++)
                indices[nIndices + i]--;
            
            nIndices += 3;
            if(nIndices == maxIndices)
            {
                maxIndices *= 2;
                indices = (unsigned int*)realloc(indices, sizeof(unsigned int) * maxIndices * 3);
            }
        }
    }
    // close the file
    fclose(file);

    s3vMeshAttributeAdd(mesh, 3, nVertices, GL_FLOAT, vertices);
    s3vMeshAttributeAdd(mesh, 3, nNormals, GL_FLOAT, normals);
    s3vMeshSetIndexAttribute(mesh, nIndices, indices);

    free(vertices);
    free(indices);
    free(normals);
}
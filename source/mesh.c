#include "s3v/mesh.h"

void s3vMeshSetIndexAttribute(S3VMesh* mesh, unsigned int size, unsigned int* buffer)
{
    assert(mesh);
    assert(mesh->indexAttribute.glVBO == 0);

    S3VMeshAttribute* attr = &mesh->indexAttribute;
    attr->sizeInBytes = sizeof(GL_UNSIGNED_INT) * size;
    attr->data = buffer;

    glBindVertexArray(mesh->glVAO);

    glGenBuffers(1, &attr->glVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, attr->glVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, attr->sizeInBytes, buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void s3vMeshAttributeAdd(S3VMesh* mesh, unsigned int nComponents, unsigned int size, int type, void* buffer)
{

    // nComponents - 3 for x, y, z
    // type - GL_FLOAT
    // size - n of vertices

    assert(mesh);

    S3VMeshAttribute* attr = &mesh->attributes[mesh->nAttributes];
    attr->sizeInBytes = sizeof(type) * nComponents * size;
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
    glGenVertexArrays(1, &mesh->glVAO);
    mesh->nAttributes = 0;
    mesh->indexAttribute.glVBO = 0;
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
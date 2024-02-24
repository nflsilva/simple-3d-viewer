#include "s3v/mesh.h"

S3VMesh* s3vMeshCreate()
{
    S3VMesh* mesh = (S3VMesh*)malloc(sizeof(S3VMesh));
    mesh->maxDistance = 0;
    return mesh;
}

void s3vMeshInit(S3VMesh* mesh, S3VMeshVertex* vertices, int nVertices, unsigned int* indices, int nElements)
{
    assert(mesh);
    glGenVertexArrays(1, &mesh->glVAO);
    glBindVertexArray(mesh->glVAO);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL Error: %d\n", error);
    }

    // buffer vertices
    glGenBuffers(1, &mesh->glVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->glVBO);
    glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(S3VMeshVertex), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(S3VMeshVertex), (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(S3VMeshVertex), (GLvoid*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(S3VMeshVertex), (GLvoid*)(6 * sizeof(float)));

    error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL Error: %d\n", error);
    }

    // buffer elements
    glGenBuffers(1, &mesh->glEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->glEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nElements * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    mesh->nElements = nElements;
    mesh->maxElements = nElements;
    
    error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL Error: %d\n", error);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}

void s3vMeshDestroy(S3VMesh* mesh)
{
    assert(mesh);
    glDeleteVertexArrays(1, &mesh->glVAO);
    glDeleteBuffers(1, &mesh->glVBO);
    glDeleteBuffers(1, &mesh->glEBO);
    free(mesh);
}

void s3vMeshBind(S3VMesh* mesh)
{
    assert(mesh);

    glBindVertexArray(mesh->glVAO);
    for(unsigned int i = 0; i < 3; i++) 
    {
        glEnableVertexAttribArray(i);

        //S3VMeshAttribute* attr = &mesh->attributes[i];
        //glBindBuffer(GL_ARRAY_BUFFER, attr->glVBO);
        //glBufferSubData(GL_ARRAY_BUFFER, 0, attr->sizeInBytes, attr->data);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->glEBO);
    //S3VMeshAttribute* iAttr = &mesh->indexAttribute;
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iAttr->glVBO);
    //glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, iAttr->sizeInBytes, iAttr->data);
}

void s3vMeshUnbind()
{
    glBindVertexArray(0);
}

static float maxAbs(float f0, float f1)
{
    if(f0 < 0) 
        f0 *= -1;

    if(f1 < 0) 
        f1 *= -1;

    if(f0 > f1)
        return f0;
    return f1; 
}

void s3vMeshCreateFromFile(const char* directoryPath, S3VMesh* mesh)
{
    assert(mesh);
    mesh->maxDistance = 0;
    mesh->nElements = 0;
    
    FILE *file = fopen(directoryPath, "r");
    
    // check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // buffer to store each line
    char line[100];
    char vertixId[30];
    float x, y, z;
    int p, c, n;
    unsigned int nVertices = 0;

    CUTILVector* positions = cutilVectorCreate(1024 * 3, sizeof(float));
    CUTILVector* normals = cutilVectorCreate(1024 * 3, sizeof(float));
    CUTILVector* uvs = cutilVectorCreate(1024 * 2, sizeof(float));
    CUTILVector* faces = cutilVectorCreate(1024 * 4, sizeof(int));
    CUTILHashTable* indexPerVertix = cutilHashTableCreate();
    
    // read the file line by line
    while (fgets(line, sizeof(line), file) != NULL) 
    {
        if(line[0] == 'f' ||  line[0] == 'a')
        {

            if(line[0] == 'a') {
                printf("H");
            }

            char* faceStart = line + 2;
            for(int i = 0; i < 3; i++) 
            {
                p = c = n = 0;

                // has all 3 attributes
                if(sscanf(faceStart, "%d/%d/%d", &p, &c, &n) == 3) 
                    sprintf(vertixId, "%d/%d/%d", p, c, n);
                    
                // has position and texture coordinates
                else if(sscanf(faceStart, "%d/%d", &p, &c) == 2)
                    sprintf(vertixId, "%d/%d", p, c);
                
                // has position and normal
                else if(sscanf(faceStart, "%d//%d", &p, &n) == 2)
                    sprintf(vertixId, "%d//%d", p, n);
            
                else 
                    printf("invalid face %d from %s\n", i, line);

                faceStart += strlen(vertixId) + 1;

                int* vertixIndexPtr = cutilHashTableGetElement(indexPerVertix, vertixId);
                if(vertixIndexPtr == CUTIL_NULL) 
                {
                    // TODO: i need to remove the need for this malloc...
                    vertixIndexPtr = malloc(sizeof(unsigned int));
                    *vertixIndexPtr = nVertices;
                    cutilHashTableAddElement(indexPerVertix, vertixId, (void*)vertixIndexPtr);
                    nVertices++;
                }

                cutilVectorPush(faces, &p);
                cutilVectorPush(faces, &c);
                cutilVectorPush(faces, &n);
                cutilVectorPush(faces, vertixIndexPtr);
            }
        }
        else if(line[0] == 'v' && line[1] == 'n')
        {
            sscanf(line, "vn %f %f %f", &x, &y, &z);
            cutilVectorPush(normals, &x);
            cutilVectorPush(normals, &y);
            cutilVectorPush(normals, &z);
        }
        else if(line[0] == 'v' && line[1] == 't')
        {
            sscanf(line, "vt %f %f", &x, &y);
            cutilVectorPush(uvs, &x);
            cutilVectorPush(uvs, &y);
        }
        else if(line[0] == 'v')
        {
            sscanf(line, "v %f %f %f", &x, &y, &z);

            mesh->maxDistance = maxAbs(mesh->maxDistance, x);
            mesh->maxDistance = maxAbs(mesh->maxDistance, y);
            mesh->maxDistance = maxAbs(mesh->maxDistance, z);

            cutilVectorPush(positions, &x);
            cutilVectorPush(positions, &y);
            cutilVectorPush(positions, &z);
        }
    }
    // close the file
    fclose(file);

    unsigned int nElements = faces->count / 4;
    S3VMeshVertex* vertices = (S3VMeshVertex*)malloc(sizeof(S3VMeshVertex) * nVertices);
    unsigned int* indices = (unsigned int*)malloc(sizeof(unsigned int) * nElements);

    int duplicated = 0;
    for(unsigned int i = 0; i < nElements; i++)
    {

        unsigned int vIndex = ((unsigned int*)faces->data)[i * 4 + 3];
        indices[i] = vIndex;
        if(vIndex < (i - duplicated)) 
        {
            duplicated++;
            continue;
        }
            
        int positionIndex = ((int*)faces->data)[i * 4 + 0];
        int uvIndex = ((int*)faces->data)[i * 4 + 1];
        int normalIndex = (( int*)faces->data)[i * 4 + 2];

        if(positionIndex < 0) 
            positionIndex = (positions->count / 3) - positionIndex;

        vertices[vIndex].position[0] = ((float*)positions->data)[(positionIndex - 1) * 3 + 0];
        vertices[vIndex].position[1] = ((float*)positions->data)[(positionIndex - 1) * 3 + 1];
        vertices[vIndex].position[2] = ((float*)positions->data)[(positionIndex - 1) * 3 + 2];

        if(normalIndex != 0) 
        {
            if(normalIndex < 0) 
                normalIndex = (normals->count / 3) - normalIndex;
            vertices[vIndex].normal[0] = ((float*)normals->data)[(normalIndex - 1) * 3 + 0];
            vertices[vIndex].normal[1] = ((float*)normals->data)[(normalIndex - 1) * 3 + 1];
            vertices[vIndex].normal[2] = ((float*)normals->data)[(normalIndex - 1) * 3 + 2];
        }

        if(uvIndex != 0) 
        {
            if(uvIndex < 0) 
                uvIndex = (uvs->count / 2) - uvIndex;
            vertices[vIndex].uv[0] = ((float*)uvs->data)[(uvIndex - 1) * 2 + 0];
            vertices[vIndex].uv[1] = ((float*)uvs->data)[(uvIndex - 1) * 2 + 1];
        }

    }

    for(unsigned int i = 0; i < nVertices; i++)
    {
        S3VMeshVertex v = vertices[i];
        //printf("%d %f %f %f\n", i, v.position[0], v.position[1], v.position[2]);
        //printf("%f\n", v->normal[0]);
    }
    printf("%d\n", duplicated);

    for(unsigned int i = 0; i < 220; i++)
    {
        S3VMeshVertex v = vertices[indices[i]];
        //printf("%d %d %f %f %f\n", i, indices[i], v.position[0], v.position[1], v.position[2]);
    }
    printf("\n");

    s3vMeshInit(mesh, vertices, nVertices, indices, nElements);

    cutilVectorDestroy(positions);
    cutilVectorDestroy(normals);
    cutilVectorDestroy(uvs);
    cutilVectorDestroy(faces);
}
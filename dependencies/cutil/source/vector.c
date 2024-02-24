#include "cutil/vector.h"

CUTILVector* cutilVectorCreate(int initialCapacity, int elementSize)
{
    CUTILVector* vec = (CUTILVector*)malloc(sizeof(CUTILVector));
    cutilVectorInit(vec, initialCapacity, elementSize);
    return vec;
}

void cutilVectorInit(CUTILVector* vector, int initialCapacity, int elementSize)
{   
    assert(vector);
    vector->data = malloc(initialCapacity * elementSize);
    vector->count = 0;
    vector->capacity = initialCapacity;
    vector->elementSize = elementSize;
}

void cutilVectorDestroy(CUTILVector* vector)
{
    assert(vector);
    free(vector->data);
    free(vector);
}

void cutilVectorPush(CUTILVector* vector, void* data)
{
    assert(vector);
    if(vector->count == vector->capacity)
    {
        vector->capacity *= 2;
        vector->data = realloc(vector->data, vector->capacity * vector->elementSize);
    }

    void* dest = vector->data + vector->count * vector->elementSize;
    memcpy(dest, data, vector->elementSize);
    vector->count++;
}

void* cutilVectorGet(CUTILVector* vector, unsigned int index)
{
    assert(vector);
    assert(vector->capacity > index);

    void* dest = vector->data + index * vector->elementSize;
    return dest;
}
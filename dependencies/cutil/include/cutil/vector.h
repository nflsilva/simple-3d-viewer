#ifndef _CUTIL_VECTOR_H
#define _CUTIL_VECTOR_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void* data;
    unsigned int count, capacity, elementSize;
} CUTILVector;

CUTILVector* cutilVectorCreate(int initialCapacity, int size);

void cutilVectorInit(CUTILVector* vector, int initialCapacity, int size);

void cutilVectorDestroy(CUTILVector* vector);

void cutilVectorPush(CUTILVector* vector, void* data);

void* cutilVectorGet(CUTILVector* vector, unsigned int index);

#endif
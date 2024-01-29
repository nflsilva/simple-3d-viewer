#ifndef _CUTIL_SORT_H
#define _CUTIL_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * Sorts an array of elements using Merge sort
 * @param data A pointer to the elements array.
 * @param typeSize The size of each element.
 * @param length The size of the elements array.
 * @param compare A pointer to a function which compares two elements for sorting
 */
void cutilSortMergeSort(void* data, int typeSize, int length, int(*compare)(const void*, const void*));

#endif
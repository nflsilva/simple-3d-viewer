#ifndef _CUTIL_FILESYSTEM_H
#define _CUTIL_FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "cutil/list.h"
#include "cutil/sort.h"

#define CUTIL_FS_READ_CHUNK_SIZE 1024
#define MAX_DIRECTORY_CONTENTS 1024
#define MAX_PATH_NAME_SIZE 1024

typedef struct CUTILFilesystemItem {
	char name[256];
	int isDirectory;
	int isSelected;
} CUTILFilesystemItem;

typedef struct CUTILFileBrowser {
	CUTILFilesystemItem directoryContents[MAX_DIRECTORY_CONTENTS];
	int directoryContentsSize;
	char directoryPathBuffer[MAX_PATH_NAME_SIZE];
	char selectedItemPathBuffer[MAX_PATH_NAME_SIZE];
} CUTILFileBrowser;

CUTILFileBrowser* cutilFileBrowserInit(const char* directoryPath);

void cutilFileBrowserDestroy(CUTILFileBrowser* fileBrowser);

char* cutilFileBrowserSelectItem(CUTILFileBrowser* fileBrowser, int itemIndex);

void cutilFileBrowserNavigateOut(CUTILFileBrowser* fileBrowser);

void cutilFileBrowserLoadDirectoryContents(CUTILFileBrowser* fileBrowser);

/*!
 * Loads into memory the contents of a file.
 * @param filePath The path to the asset to load
 * @return The data from the file, in bytes. `NULL` if the file doesn't exist.
 */
const char* cutilFileBrowserLoadFile(const char* filePath);

#endif
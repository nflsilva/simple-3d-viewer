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
#define MAX_EXTENSION_SIZE 10

/*!
 * Represents a file system item.
 * @param name The name of the item.
 * @param isDirectory Indicates if the item is a file or a directory.
 * @param isSelected Indicates if the item was selected.
 */
typedef struct CUTILFilesystemItem {
	char name[256];
	int isDirectory;
	int isSelected;
} CUTILFilesystemItem;

/*!
 * Represents a file system context.
 * @param directoryContents An array of items from the current directory.
 * @param directoryContentsSize The number of items on the current directory.
 * @param directoryPathBuffer The full path for the current directory.
 * @param selectedItemPathBuffer The full path for the selected file.
 */
typedef struct CUTILFileBrowser {
	CUTILFilesystemItem directoryContents[MAX_DIRECTORY_CONTENTS];
	int directoryContentsSize;
	char directoryPathBuffer[MAX_PATH_NAME_SIZE];
	char selectedItemPathBuffer[MAX_PATH_NAME_SIZE];
	char fileExtensionBuffer[MAX_EXTENSION_SIZE];
} CUTILFileBrowser;

/*!
 * Creates and initialises a `fileBrowser` struct
 * @param directoryPath The initial directory of the file browser
 */
CUTILFileBrowser* cutilFileBrowserInit(const char* directoryPath, const char* fileExtension);

/*!
 * Destroys and cleans up a `fileBrowser` struct
 * @param fileBrowser A pointer to the filebrowser struct
 */
void cutilFileBrowserDestroy(CUTILFileBrowser* fileBrowser);

/*!
 * Select a specific item from the current directory on file browser.
 * If item is a directory, `fileBrowser` struct will be updated with the new directory contents.
 * If item is a file, the file path should be returned.
 * @param fileBrowser A pointer to the filebrowser struct
 * @param itemIndex The item index to select
 * @return If item is a file, the file path is returned. `NULL` if it is a directory.
 */
char* cutilFileBrowserSelectItem(CUTILFileBrowser* fileBrowser, int itemIndex);

/*!
 * Loads the contents of the current directory in file browser
 * @param fileBrowser A pointer to the filebrowser struct
 */
void cutilFileBrowserLoadDirectoryContents(CUTILFileBrowser* fileBrowser);

/*!
 * Loads into memory the contents of a file.
 * @param filePath The path to the asset to load
 * @return The data from the file, in bytes. `NULL` if the file doesn't exist.
 */
const char* cutilFileBrowserLoadFile(const char* filePath);

#endif
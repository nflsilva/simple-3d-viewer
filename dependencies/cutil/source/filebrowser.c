#include "cutil/filebrowser.h"

CUTILFileBrowser* cutilFileBrowserInit(const char* directoryPath)
{
    CUTILFileBrowser* browser = (CUTILFileBrowser*) malloc(sizeof(CUTILFileBrowser));
    browser->directoryContentsSize = 0;
    strcpy(browser->directoryPathBuffer, directoryPath);
    cutilFileBrowserLoadDirectoryContents(browser);
    return browser;
}

void cutilFileBrowserDestroy(CUTILFileBrowser* fileBrowser)
{
    if(!fileBrowser) return;
    free(fileBrowser);
}

char* cutilFileBrowserSelectItem(CUTILFileBrowser* fileBrowser, int itemIndex)
{
    if(!fileBrowser || itemIndex < 0 || itemIndex >= fileBrowser->directoryContentsSize) 
        return NULL;

    CUTILFilesystemItem* item = &fileBrowser->directoryContents[itemIndex];

    if(item->isDirectory)
    {
        // TODO: we should create a cross-platform component to deal with
        // file paths
        strcat(fileBrowser->directoryPathBuffer, "/");
        strcat(fileBrowser->directoryPathBuffer, item->name);
        cutilFileBrowserLoadDirectoryContents(fileBrowser);
        return NULL;
    }

    strcpy(fileBrowser->selectedItemPathBuffer, fileBrowser->directoryPathBuffer);
    strcat(fileBrowser->selectedItemPathBuffer, "/");
    strcat(fileBrowser->selectedItemPathBuffer, item->name);
    for(int i = 0; i < fileBrowser->directoryContentsSize; i++) 
        fileBrowser->directoryContents[i].isSelected = 0;

    item->isSelected = 1;
    return fileBrowser->selectedItemPathBuffer;
}

static int filesystemItemComparator(const void* a, const void* b) 
{
    return strcmp(((CUTILFilesystemItem*)a)->name, ((CUTILFilesystemItem*)b)->name);
}

void cutilFileBrowserLoadDirectoryContents(CUTILFileBrowser* fileBrowser)
{
    if(!fileBrowser) return;

	DIR* pdir = opendir(fileBrowser->directoryPathBuffer);
	if (!pdir) return;
    
    fileBrowser->directoryContentsSize = 0;
    struct dirent* pent;
    while ((pent = readdir(pdir)) != NULL) 
    {
        CUTILFilesystemItem* item = &fileBrowser->directoryContents[fileBrowser->directoryContentsSize];

        // ignore self
        if(strcmp(pent->d_name, ".") == 0) continue;

        strcpy(item->name, pent->d_name);
        item->isDirectory = pent->d_type == DT_DIR;
        item->isSelected = 0;
        fileBrowser->directoryContentsSize++;
    }
    closedir(pdir);

    // sort items for convenience
    cutilSortMergeSort(
        fileBrowser->directoryContents, 
        sizeof(CUTILFilesystemItem),
        fileBrowser->directoryContentsSize,
        &filesystemItemComparator
    );
}

const char* cutilFileBrowserLoadFile(const char* filePath)
{

    FILE *file = NULL;
    file = fopen(filePath, "r");
    if(!file) return NULL;

    unsigned long readSize = 0;
    unsigned long contentSize = 0;
    unsigned long fileContentBufferSize = CUTIL_FS_READ_CHUNK_SIZE * 10;
    char* fileContentBuffer = (char*)malloc(sizeof(char) * (fileContentBufferSize + 1));
    int didError = 0;
    do
    {
        readSize = fread(&fileContentBuffer[contentSize], sizeof(char), CUTIL_FS_READ_CHUNK_SIZE, file);
        if (ferror(file))
        {
            didError = 1;
            break;
        }

        contentSize += readSize;
        if(contentSize == fileContentBufferSize)
        {
            fileContentBufferSize = fileContentBufferSize + CUTIL_FS_READ_CHUNK_SIZE * 10;
            char* newContent = realloc(fileContentBuffer, fileContentBufferSize);
            if(!newContent)
            {
                didError = 1;
                break;
            }
            fileContentBuffer = newContent;
        }

    } while (readSize == CUTIL_FS_READ_CHUNK_SIZE);

    fclose(file);
    if(didError)
    {
        free(fileContentBuffer);
        return NULL;
    }

    fileContentBuffer[contentSize] = '\0';
    return fileContentBuffer;
}

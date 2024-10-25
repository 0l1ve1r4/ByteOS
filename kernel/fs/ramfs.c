#include <fs/tmpfs.h>
#include <kernel/heap.h>
#include <string.h>
#include <stdio.h>

static TmpFs tmpfs;

u8 ramfs_init(void) {
    tmpfs.root.file_count = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        tmpfs.root.files[i] = NULL;
    }

    return 0;
}

File* ramfs_create_file(const char* name, u32 size) {
    if (tmpfs.root.file_count >= MAX_FILES) {
        printf("[tmpfs.c]: No space for more files\n");
        return NULL;
    }


    File* file = (File*)kMalloc(sizeof(File));
    if (!file) {
        printf("[tmpfs.c]: Failed to allocate file structure\n");
        return NULL;  
    }

    strncpy(file->name, name, MAX_FILE_NAME_LEN);
    file->size = size;
    file->used = 1;

    file->data = (u8*)kMalloc(size);  
    if (!file->data) {
        printf("[tmpfs.c]: File data allocation fails\n");
        kFree(file);  
        return NULL;
    }

    tmpfs.root.files[tmpfs.root.file_count++] = file;
    return file;
}

int ramfs_write_file(File* file, const u8* data, u32 size) {
    if (file == NULL || size > file->size) {
        printf("[tmpfs.c]: Invalid file or size too large\n");
        return -1;  
    }

    memcpy(file->data, data, size);
    return 0;
}


int ramfs_read_file(File* file, u8* buffer, u32 size) {
    if (file == NULL || size > file->size) {
        printf("[tmpfs.c]: Invalid file or size too large\n");
        return -1;
    } 

    memcpy(buffer, file->data, size);
    return 0;
}

int ramfs_delete_file(const char* name) {
    for (u32 i = 0; i < tmpfs.root.file_count; i++) {
        if (strcmp(tmpfs.root.files[i]->name, name) == 0) {
            kFree(tmpfs.root.files[i]->data);  
            kFree(tmpfs.root.files[i]);        

            // Shift remaining files to maintain compact file array
            for (u32 j = i; j < tmpfs.root.file_count - 1; j++) {
                tmpfs.root.files[j] = tmpfs.root.files[j + 1];
            }
            tmpfs.root.file_count--;
            return 0;
        }
    }

    printf("[tmpfs.c]: File not found\n");
    return -1;  
}

void ramfs_ls() {
    if (tmpfs.root.file_count == 0) {
        printf("No files in directory.\n");
        return;
    }

    printf("Total: %i\n", tmpfs.root.file_count);
    printf("FILE \t CREATOR \t SIZE (B) \t CREATION \n");
    for (u32 i = 0; i < tmpfs.root.file_count; i++) {
        printf("%s \t root \t %i \t NULL\n", 
            tmpfs.root.files[i]->name, tmpfs.root.files[i]->size);
    }
}

void ramfs_cat(const char* name) {
    for (u32 i = 0; i < tmpfs.root.file_count; i++) {
        File* file = tmpfs.root.files[i];
        if (strcmp(file->name, name) == 0) {
            printf("%s\n", file->data);
            return;
        }
    }
    printf("File not found: %s\n", name);
}

File* ramfs_find_file(const char* name) {
    for (u32 i = 0; i < tmpfs.root.file_count; i++) {
        if (strcmp(tmpfs.root.files[i]->name, name) == 0) {
            return tmpfs.root.files[i];
        }
    }
    return NULL;  // File not found
}


// Example to demonstrate the ls and cat functionality
void example_ls_cat_usage() {
    ramfs_init();

    // Create a file
    File* file1 = ramfs_create_file("file1.txt", 50);
    const char* content1 = "This is the content of file1.";
    ramfs_write_file(file1, (const u8*)content1, strlen(content1));

    // Create another file
    File* file2 = ramfs_create_file("file2.txt", 30);
    const char* content2 = "File2 contains this text.";
    ramfs_write_file(file2, (const u8*)content2, strlen(content2));

    // List files in the filesystem
    printf("Listing files:\n");
    ramfs_ls();

    // Display the content of file1
    printf("\nDisplaying file1 content:\n");
    ramfs_cat("file1.txt");

    // Display the content of file2
    printf("\nDisplaying file2 content:\n");
    ramfs_cat("file2.txt");

    // Try to display a non-existent file
    printf("\nAttempting to display a non-existent file:\n");
    ramfs_cat("file3.txt");
}

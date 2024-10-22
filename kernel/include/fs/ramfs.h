#ifndef RAMFS_H
#define RAMFS_H

#define MAX_FILES 128
#define MAX_FILE_NAME_LEN 64
#define MAX_FILE_SIZE 255

#include <types.h>

typedef struct File {
    char name[MAX_FILE_NAME_LEN];
    u32 size;
    u8* data;
    u8 used;
} File;

typedef struct Directory {
    File* files[MAX_FILES];
    u32 file_count;
} Directory;

typedef struct RamFs {
    Directory root;
} RamFs;

u8 ramfs_init(void);

File* ramfs_create_file(const char* name, u32 size);

int ramfs_write_file(File* file, const u8* data, u32 size);

int ramfs_read_file(File* file, u8* buffer, u32 size);

int ramfs_delete_file(const char* name);

void ramfs_ls();

void ramfs_cat(const char* name);

File* ramfs_find_file(const char* name);

#endif
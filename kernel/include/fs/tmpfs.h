//========================================================================
//    This file is part of ByteOS.
//    Copyright (C) 2024 Guilherme Oliveira Santos
//    This is free software: you can redistribute it and/or modify it 
//    under the terms of the GNU GPL3 or (at your option) any later version. 
//	
//	* File: tmpfs.h 
//	* Sources: 
//	* Description: Temporary Filesystem   
//========================================================================

//========================================================================
                                #ifndef RAMFS_H
                                #define RAMFS_H
//========================================================================

//========================================================================
// 	                                INCLUDES
//========================================================================

#include <types.h>

//========================================================================
// 	                                DEFINES
//========================================================================

#define MAX_FILES 128
#define MAX_FILE_NAME_LEN 64
#define MAX_FILE_SIZE 255

//========================================================================
// 	                                ENUMS
//========================================================================

//========================================================================
// 	                                STRUCTS
//========================================================================

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

typedef struct TmpFs {
    Directory root;
} TmpFs;

//========================================================================
// 	                                FUNCIONS
//========================================================================

u8 ramfs_init(void);

File* ramfs_create_file(const char* name, u32 size);

int ramfs_write_file(File* file, const u8* data, u32 size);

int ramfs_read_file(File* file, u8* buffer, u32 size);

int ramfs_delete_file(const char* name);

void ramfs_ls();

void ramfs_cat(const char* name);

File* ramfs_find_file(const char* name);

//========================================================================
 	                                #endif
//========================================================================
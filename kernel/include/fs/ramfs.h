#define MAX_FILES 128
#define MAX_FILE_NAME_LEN 64
#define MAX_FILE_SIZE 4096

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

RamFs ramfs;

//
// Created by olegshipu on 19.01.24.
//

#ifndef UNTITLED_OS_FS_H
#define UNTITLED_OS_FS_H
#include "../kalloc/kalloc.h"
#include "../memlayout.h"
#define FILE_SYSTEM_SIZE 10240
#define MAX_FILENAME_LENGTH 16
#define MAX_FILE_COUNT 16
#define MAX_DIR_COUNT 8
#define MAX_ENTRIES_PER_DIR 8

typedef struct {
    char *filename;
    int start_page;
    int page_count;
} FileEntry;

typedef struct {
    char dirname[MAX_FILENAME_LENGTH];
    int entry_count;
    FileEntry entries[MAX_ENTRIES_PER_DIR];
} Directory;

typedef struct {
    Directory *root_directory;
    Directory directories[MAX_DIR_COUNT];
    int dir_count;
    FileEntry files[MAX_FILE_COUNT];
    int file_count;
    PageTableEntry page_table[FILE_SYSTEM_SIZE / PGSIZE];
    char data[FILE_SYSTEM_SIZE];
} FileSystem;

#endif //UNTITLED_OS_FS_H

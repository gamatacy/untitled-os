/*

void initialize_file_system(FileSystem* fs) {
    memset(fs, 0, sizeof(FileSystem));
}

int create_file(FileSystem* fs, const char* filename, int size) {
    if (fs->file_count >= MAX_FILE_COUNT) {
        return -1; // No space for a new file
    }

    strncpy(fs->files[fs->file_count].filename, filename, MAX_FILENAME_LENGTH - 1);
    fs->files[fs->file_count].filename[MAX_FILENAME_LENGTH - 1] = '\0';
    fs->files[fs->file_count].start_page = fs->file_count + 1;
    fs->files[fs->file_count].page_count = size;

    fs->file_count++;
    return fs->file_count;
}

int create_directory(FileSystem* fs, const char* dirname) {
    if (fs->dir_count >= MAX_DIR_COUNT) {
        return -1; // No space for a new directory
    }

    strncpy(fs->directories[fs->dir_count].dirname, dirname, MAX_FILENAME_LENGTH - 1);
    fs->directories[fs->dir_count].dirname[MAX_FILENAME_LENGTH - 1] = '\0';
    fs->directories[fs->dir_count].entry_count = 0;

    fs->dir_count++;
    return fs->dir_count;
}

void add_file_to_directory(FileSystem* fs, int dir_id, int file_id) {
    if (dir_id > 0 && dir_id <= MAX_DIR_COUNT && file_id > 0 && file_id <= fs->file_count) {
        Directory* dir = &fs->directories[dir_id - 1];
        if (dir->entry_count < MAX_ENTRIES_PER_DIR) {
            dir->entries[dir->entry_count++] = fs->files[file_id - 1];
        }
    }
}

void write_page(FileSystem* fs, int page_num, const char* data) {
    if (page_num > 0 && page_num <= FILE_SYSTEM_SIZE / PGSIZE) {
        memcpy(&fs->data[(page_num - 1) * PGSIZE], data, PGSIZE);
    }
}

void write_file(FileSystem* fs, int file_id, const char* data) {
    if (file_id > 0 && file_id <= fs->file_count) {
        FileEntry* file = &fs->files[file_id - 1];
        int current_page = file->start_page;
        int remaining_pages = file->page_count;

        while (remaining_pages > 0) {
            write_page(fs, current_page, data);
            data += PGSIZE;
            current_page++;
            remaining_pages--;
        }
    }
}

void read_page(const FileSystem* fs, int page_num, char* data) {
    if (page_num > 0 && page_num <= FILE_SYSTEM_SIZE / PGSIZE) {
        memcpy(data, &fs->data[(page_num - 1) * PGSIZE], PGSIZE);
    }
}

void read_file(const FileSystem* fs, int file_id, char* data) {
    if (file_id > 0 && file_id <= fs->file_count) {
        const FileEntry* file = &fs->files[file_id - 1];
        int current_page = file->start_page;
        int remaining_pages = file->page_count;

        while (remaining_pages > 0) {
            read_page(fs, current_page, data);
            data += PGSIZE;
            current_page++;
            remaining_pages--;
        }
    }
}
*/

/*
int main() {
    FileSystem fs;
    initialize_file_system(&fs);

    int file_id = create_file(&fs, "example.txt", 3);
    if (file_id != -1) {
        const char* data_to_write = "Hello, this is an example file!";
        write_file(&fs, file_id, data_to_write);

        char data_read[PGSIZE * 3 + 1]; // +1 for null terminator
        read_file(&fs, file_id, data_read);

        printf("File content: %s\n", data_read);
    } else {
        printf("Failed to create file.\n");
    }

    int dir_id = create_directory(&fs, "documents");
    if (dir_id != -1) {
        add_file_to_directory(&fs, dir_id, file_id);
        printf("File added to directory.\n");
    } else {
        printf("Failed to create directory.\n");
    }

    return 0;
}
*/

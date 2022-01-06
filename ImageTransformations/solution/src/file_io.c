#include "../include/file_io.h"

bool open_file(FILE** file, const char* filename, const char* mode) {
    *file = fopen(filename, mode);
    return (bool) (*file != NULL); // 0 - opened, 1 - not opened
}

bool close_file(FILE** file) {
    int result = fclose(*file);
    return (result == 0);
}

#ifndef FILE_IO_H
#define FILE_IO_H
#include <stdbool.h>
#include <stdio.h>

bool open_file(FILE** file, const char* filename, const char* mode);
bool close_file(FILE** file);


#endif //FILE_IO_H

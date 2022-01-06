#ifndef BMP_IO_H
#define BMP_IO_H
#include "../include/memory.h"
#include "../include/structures.h"
#include <stdio.h>

enum read_status {
    READ_OK = 0,
    READ_INVALID_HEADER,
    READ_NULL,
    READ_ERROR
};

enum write_status {
    WRITE_OK = 0,
    WRITE_NULL,
    WRITE_ERROR
};

enum read_status from_bmp(FILE* file_in, struct image* img);
enum write_status to_bmp(FILE* file_out, struct image* img);

#endif //BMP_IO_H

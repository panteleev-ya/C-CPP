#ifndef MEMORY_H
#define MEMORY_H
#include "../include/structures.h"
#include <stdbool.h>

bool pixels_malloc_memory(struct pixel** pixels, uint64_t width, uint64_t height);
void pixels_free_memory(struct pixel* pixels);

bool header_malloc_memory(struct bmp_header** header);
void header_free_memory(struct bmp_header* header);

#endif //MEMORY_H

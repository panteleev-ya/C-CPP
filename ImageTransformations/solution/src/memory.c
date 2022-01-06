#include "../include/memory.h"
#include <stdlib.h>

bool pixels_malloc_memory(struct pixel** pixels, uint64_t width, uint64_t height) {
    *pixels = malloc(sizeof(struct pixel) * width * height);
    return (bool) (pixels == NULL);
}

void pixels_free_memory(struct pixel* pixels) {
    free(pixels);
}

bool header_malloc_memory(struct bmp_header** header) {
    *header = malloc(sizeof(struct bmp_header));
    return (bool) (header == NULL);
}
void header_free_memory(struct bmp_header* header) {
    free(header);
}

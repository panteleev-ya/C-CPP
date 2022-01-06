#include "../include/transformations.h"
#include "../include/memory.h"
#include <stdlib.h>

struct image image_create(uint64_t width, uint64_t height) {
    struct image new_img;
    new_img.width = width;
    new_img.height = height;
    pixels_malloc_memory(&new_img.data, width, height);
    return new_img;
}

struct image rotate_counterclock_wise_90(const struct image img){
    struct image rotated_img = image_create(img.height, img.width);

    for (size_t i = 0; i < img.height; i++) {
        for (size_t j = 0; j < img.width; j++) {
            *(rotated_img.data + j * img.height + (img.height - 1 - i)) = *(img.data + i * img.width + j);
        }
    }

    return rotated_img;
}

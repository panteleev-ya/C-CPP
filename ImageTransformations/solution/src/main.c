#include "../include/bmp_io.h"
#include "../include/file_io.h"
#include "../include/transformations.h"

int main(int argc, char** argv) {
    bool input_file_opened, output_file_opened;
    bool input_file_closed, output_file_closed;
    char* input_filename = NULL;
    char* output_filename = NULL;
    struct image img;
    struct image rotated_image;
    FILE* input_file = NULL;
    FILE* output_file = NULL;

    // Reading command line arguments
    if (argc < 3) {
        fprintf(stderr, "Not enough command line arguments\n");
        return -1;
    }
    input_filename = argv[1];
    output_filename= argv[2];
    
    // Opening input and output files
    input_file_opened = !open_file(&input_file, input_filename, "rb");
    output_file_opened = !open_file(&output_file, output_filename, "wb");
    if (input_file_opened) {
        fprintf(stderr, "Cannot open input file\n");
        if (!output_file_opened) {
            output_file_closed = close_file(&output_file);
            if (output_file_closed) {
                fprintf(stderr, "Cannot close files\n");
            }
        }
        return -1;
    }
    if (output_file_opened) {
        fprintf(stderr, "Cannot create new .bmp file\n");
        if (!input_file_opened) {
            input_file_closed = close_file(&input_file);
            if (input_file_closed) {
                fprintf(stderr, "Cannot close files\n");
            }
        }
        return -1;
    }
    fprintf(stdout, "Files were successfully opened\n");

    // Reading input file as .bmp
    if (from_bmp(input_file, &img)) {
        fprintf(stderr, "Cannot read file as .bmp file, may be its not actually a .bmp file\n");\
        if (!input_file_opened) {
            input_file_closed = close_file(&input_file);
            if (input_file_closed) {
                fprintf(stderr, "Cannot close files\n");
            }
        }
        if (!output_file_opened) {
            output_file_closed = close_file(&output_file);
            if (output_file_closed) {
                fprintf(stderr, "Cannot close files\n");
            }
        }
        return -1;
    }
    fprintf(stdout, "File was successfully read\n");

    // Rotating image by 90 degree counterclock-wise
    rotated_image = rotate_counterclock_wise_90(img);

    // Writing rotated image in output file
    if (to_bmp(output_file, &rotated_image)) {
        fprintf(stderr, "Cannot convert image into .bmp\n");

        pixels_free_memory(rotated_image.data);
        pixels_free_memory(img.data);
        if (!input_file_opened) {
            input_file_closed = close_file(&input_file);
            if (input_file_closed) {
                fprintf(stderr, "Cannot close files\n");
            }
        }
        if (!output_file_opened) {
            output_file_closed = close_file(&output_file);
            if (output_file_closed) {
                fprintf(stderr, "Cannot close files\n");
            }
        }
        return -1;
    }
    fprintf(stdout, "Image was successfully converted into .bmp\n");

    // Closing input and output files
    input_file_closed = !close_file(&input_file);
    output_file_closed = !close_file(&output_file);
    if (input_file_closed || output_file_closed) {
        fprintf(stderr, "Cannot close files\n");
        pixels_free_memory(rotated_image.data);
        pixels_free_memory(img.data);
        return -1;
    }
    fprintf(stdout, "Files were successfully closed\n");

    // Freeing memory
    pixels_free_memory(rotated_image.data);
    pixels_free_memory(img.data);
    return 0;
}

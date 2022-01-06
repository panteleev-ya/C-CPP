#include "../include/bmp_io.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>


#define BFTYPE 0x4D42
#define BFRESERVED 0
#define BISIZE 40
#define BIPLANES 1
#define BIBITCOUNT 24
#define BICOMPRESSION 0
#define BIPELSPERMETER 2834
#define BICLRUSED 0
#define BICLRIMPORTANT 0

// static uint16_t bfType = 19778;
// static uint32_t bfReserved = 0;
// static uint32_t biSize = 40;
// static uint16_t biPlanes = 1;
// static uint16_t biBitCount = 24;
// static uint32_t biCompression = 0;
// static uint32_t biPelsPerMeter = 2834;
// static uint32_t biClrUsed = 0;
// static uint32_t biClrImportant = 0;

// Calculating padding
static size_t calculate_padding(size_t width){
	size_t padding = 4 - width * sizeof(struct pixel) % 4;
	if (padding == 4){
		padding = 0;
	}
	return padding;
}

// Reading header from bmp file
static enum read_status read_bmp_header(FILE* file_in, struct bmp_header* header) {
    if(fseek(file_in, 0, SEEK_END) != 0) {
    	return READ_INVALID_HEADER;
    }
    const size_t file_size = ftell(file_in);
    if (file_size < sizeof(struct bmp_header)) {
    	return READ_INVALID_HEADER;
    }
    rewind(file_in);
    const size_t result = fread(header, sizeof(struct bmp_header), 1, file_in);
    if(result != 1) {
    	return READ_INVALID_HEADER;
    }
    return READ_OK;
}

// Reading pixels data from bmp file
static enum read_status read_pixels(FILE* file_in, struct image* img) {
    if (pixels_malloc_memory(&img->data, img->width, img->height)) {
    	return READ_ERROR; 
    }
    const size_t padding = calculate_padding(img->width);
    for (size_t i = 0; i < img->height; i++) {
        const size_t result = fread(img->data + i * (img->width), (size_t)(img->width) * sizeof(struct pixel), 1, file_in);
        if (result != 1){
        	return READ_NULL;
        }
        if (fseek(file_in, padding, SEEK_CUR) != 0) {
        	return READ_NULL;
        }
    }
    return READ_OK;
}

// Creating new header
static enum write_status create_header(const struct image* img, struct bmp_header* header) {
    if (header == NULL) {
        return WRITE_NULL;
    }
    const size_t padding = calculate_padding(img->width);
    header->bfType = BFTYPE; // bfType;
    header->biSizeImage = (img->width * sizeof(struct pixel) + padding) * img->height;
    header->bfileSize = header->biSizeImage + sizeof(struct bmp_header);
    header->bfReserved = BFRESERVED; // bfReserved;
    header->bOffBits = sizeof(struct bmp_header);
    header->biSize = BISIZE; // biSize;
    header->biWidth = img->width;
    header->biHeight = img->height;
    header->biPlanes = BIPLANES; // biPlanes;
    header->biBitCount = BIBITCOUNT; // biBitCount;
    header->biCompression = BICOMPRESSION; // biCompression;
    header->biXPelsPerMeter = BIPELSPERMETER; // biPelsPerMeter;
    header->biYPelsPerMeter = BIPELSPERMETER; // biPelsPerMeter;
    header->biClrUsed = BICLRUSED; // biClrUsed;
    header->biClrImportant = BICLRIMPORTANT; // biClrImportant;
    return WRITE_OK;
}

// Reading full bmp file by using read_bmp_header and read_pixels
enum read_status from_bmp(FILE* file_in, struct image* img) {
    if (file_in == NULL) {
    	return READ_NULL; 
    }
    
    if (img == NULL) {
    	return READ_NULL; 
    }
    
    struct bmp_header* header;
    if (header_malloc_memory(&header)) {
        return READ_NULL;
    }
    
    enum read_status header_status = read_bmp_header(file_in, header);
    if (header_status) { // if something went wrong with reading header
    	return header_status;
    }
    img->height = header->biHeight;
    img->width = header->biWidth;
    if(fseek(file_in, header->bOffBits, SEEK_SET) != 0) {
    	return READ_INVALID_HEADER;
    }
    enum read_status pixels_status = read_pixels(file_in, img);
    free(header);
    return pixels_status;
}

// Writing full bmp file
enum write_status to_bmp(FILE* file_out, struct image* img) {
    if (file_out == NULL) {
    	return WRITE_NULL;
    }
    
    if (img == NULL || img->data == NULL) {
    	return WRITE_NULL;
    }
    
    struct bmp_header* header = NULL;
    if (header_malloc_memory(&header)) {
        return WRITE_NULL;
    }
    
    create_header(img, header);
    
    const size_t count = fwrite(header, sizeof(struct bmp_header), 1, file_out);
    if (count != 1) { // cheaking if we really writing the object or not (header)
    	return WRITE_ERROR;
    }
    if (fseek(file_out, header->bOffBits, SEEK_SET) != 0){
    	return WRITE_NULL;
    }
    
    const size_t padding = calculate_padding(img->width); 
   
    const uint64_t line_padding = 0;
    
    
    
    uint64_t writing_line_of_pixels = 0;
    for (size_t i = 0; i < img->height; i++) {
        writing_line_of_pixels += fwrite(img->data + i * img->width, sizeof(struct pixel), img->width, file_out);
        
        fwrite(&line_padding, 1, padding, file_out);
        
    }
    if(writing_line_of_pixels < img->width * img->height){
    	return WRITE_ERROR;
    }
    
    free(header);
    return WRITE_OK;
}

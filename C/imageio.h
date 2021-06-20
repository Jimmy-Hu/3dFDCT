/* Develop by Jimmy Hu */

#ifndef IMAGEIO_H
#define IMAGEIO_H

#include "base.h"

RGB *raw_image_to_array(const int xsize, const int ysize, const unsigned char *image);

unsigned long bmp_read_x_size(const char *filename, const bool extension);

unsigned long bmp_read_y_size(const char *filename, const bool extension);

char bmp_read(unsigned char *image, const int xsize, const int ysize, const char *filename, const bool extension);

BMPIMAGE bmp_file_read(const char *filename, const bool extension);

int bmp_write(const char *filename, const int xsize, const int ysize, const unsigned char *image);

unsigned char *array_to_raw_image(const int xsize, const int ysize, const RGB* input_data);

unsigned char bmp_filling_byte_calc(const unsigned int xsize);

#endif


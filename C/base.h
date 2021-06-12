/* Develop by Jimmy Hu */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH 256
#define FILE_ROOT_PATH "./"

#define True true
#define False false

typedef struct RGB
{
    unsigned char channels[3];
} RGB;

typedef struct BMPIMAGE
{
    char FILENAME[MAX_PATH];
    
    unsigned int XSIZE;
    unsigned int YSIZE;
    unsigned char FILLINGBYTE;
    unsigned char *IMAGE_DATA;
} BMPIMAGE;

typedef struct RGBIMAGE
{
    unsigned int XSIZE;
    unsigned int YSIZE;
    RGB *IMAGE_DATA;
} RGBIMAGE;
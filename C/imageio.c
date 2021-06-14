/* Develop by Jimmy Hu */

#include "imageio.h"

RGB *raw_image_to_array(const int xsize, const int ysize, const unsigned char * const image)
{
    RGB *output;
    output = malloc(sizeof *output * xsize * ysize);
    if(output == NULL)
    {    
        printf("Memory allocation error!");
        return NULL;
    }        
    unsigned char FillingByte;
    FillingByte = bmp_filling_byte_calc(xsize);
    for(int y = 0; y < ysize; y++)
    {
        for(int x = 0; x < xsize; x++)
        {
            for (int color = 0; color < 3; color++) {
                output[y * xsize + x].channels[color] =
                    image[3 * (y * xsize + x) + y * FillingByte + (2 - color)];
            }
        }
    }
    return output;
}

//----bmp_read_x_size function----
unsigned long bmp_read_x_size(const char *filename, const bool extension)
{
    char fname_bmp[MAX_PATH];
    if(extension == false)
    {    
        sprintf(fname_bmp, "%s.bmp", filename);
    }        
    else
    {    
        strcpy(fname_bmp,filename);
    }    
    FILE *fp;
    fp = fopen(fname_bmp, "rb");
    if (fp == NULL) 
    {     
        printf("Fail to read file!\n");
        return -1;
    }             
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, fp);
    unsigned long output;
    output = header[18] + 
        ((unsigned long)header[19] << 8) +
        ((unsigned long)header[20] << 16) +
        ((unsigned long)header[21] << 24);
    fclose(fp);
    return output;
}

//---- bmp_read_y_size function ----
unsigned long bmp_read_y_size(const char * const filename, const bool extension)
{
    char fname_bmp[MAX_PATH];
    if(extension == false)
    {    
        sprintf(fname_bmp, "%s.bmp", filename);
    }        
    else
    {    
        strcpy(fname_bmp,filename);
    }    
    FILE *fp;
    fp = fopen(fname_bmp, "rb");
    if (fp == NULL)
    {
        printf("Fail to read file!\n");
        return -1;
    }             
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, fp);
    unsigned long output; 
    output= header[22] + 
        ((unsigned long)header[23] << 8) +
        ((unsigned long)header[24] << 16) +
        ((unsigned long)header[25] << 24);
    fclose(fp);
    return output;
}

//---- bmp_file_read function ---- 
char bmp_read(unsigned char * const image, const int xsize, const int ysize, const char * const filename, const bool extension)
{
    char fname_bmp[MAX_PATH];
    if(extension == false)
    {    
        sprintf(fname_bmp, "%s.bmp", filename);
    }        
    else
    {    
        strcpy(fname_bmp,filename);
    }    
    unsigned char filling_bytes;
    filling_bytes = bmp_filling_byte_calc(xsize);
    FILE *fp;
    fp = fopen(fname_bmp, "rb");
    if (fp==NULL)
    {     
        printf("Fail to read file!\n");
        return -1;
    }             
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, fp);
    fread(image, sizeof(unsigned char), (size_t)(long)(xsize * 3 + filling_bytes)*ysize, fp);
    fclose(fp); 
    return 0;
}

BMPIMAGE bmp_file_read(const char * const filename, const bool extension)
{
    BMPIMAGE output;
    stpcpy(output.FILENAME, "");
    output.XSIZE = 0;
    output.YSIZE = 0;
    output.IMAGE_DATA = NULL;
    if(filename == NULL)
    {    
        printf("Path is null\n");
        return output;
    }
    char fname_bmp[MAX_PATH];
    if(extension == false)
    {
        sprintf(fname_bmp, "%s.bmp", filename);
    }
    else
    {    
        strcpy(fname_bmp,filename);
    }    
    FILE *fp;
    fp = fopen(fname_bmp, "rb");
    if (fp == NULL)
    {     
        printf("Fail to read file!\n");
        return output;
    }             
    stpcpy(output.FILENAME, fname_bmp);
    output.XSIZE = (unsigned int)bmp_read_x_size(output.FILENAME,true);
    output.YSIZE = (unsigned int)bmp_read_y_size(output.FILENAME,true);
    if( (output.XSIZE == -1) || (output.YSIZE == -1) )
    {     
        printf("Fail to fetch information of image!");
        return output;
    }        
    else
    {     
        printf("Width of the input image: %d\n",output.XSIZE);
        printf("Height of the input image: %d\n",output.YSIZE);
        printf("Size of the input image(Byte): %d\n", (size_t)output.XSIZE * output.YSIZE * 3);
        output.FILLINGBYTE = bmp_filling_byte_calc(output.XSIZE);
        output.IMAGE_DATA = malloc(sizeof *output.IMAGE_DATA * (output.XSIZE * 3 + output.FILLINGBYTE) * output.YSIZE);
        if (output.IMAGE_DATA == NULL)
        { 
            printf("Memory allocation error!");
            return output;
        }     
        else
        {
            for(int i = 0; i < ((output.XSIZE * 3 + output.FILLINGBYTE) * output.YSIZE);i++)
            {
                output.IMAGE_DATA[i] = 255;
            }
            bmp_read(output.IMAGE_DATA, output.XSIZE, output.YSIZE, output.FILENAME, true);
        }
    }    
    return output;
}

//----bmp_write function---- 
int bmp_write(const char * const filename, const int xsize, const int ysize, const unsigned char * const image) 
{
    unsigned char FillingByte;
    FillingByte = bmp_filling_byte_calc(xsize);
    unsigned char header[54] =
    {
    0x42, 0x4d, 0, 0, 0, 0, 0, 0, 0, 0,
    54, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0                        
    };                                
    unsigned long file_size = (long)xsize * (long)ysize * 3 + 54;
    unsigned long width, height;
    char fname_bmp[MAX_PATH];
    header[2] = (unsigned char)(file_size &0x000000ff);
    header[3] = (file_size >> 8) & 0x000000ff;        
    header[4] = (file_size >> 16) & 0x000000ff;        
    header[5] = (file_size >> 24) & 0x000000ff;        
    
    width = xsize;
    header[18] = width & 0x000000ff;
    header[19] = (width >> 8) &0x000000ff;
    header[20] = (width >> 16) &0x000000ff;
    header[21] = (width >> 24) &0x000000ff;
     
    height = ysize;
    header[22] = height &0x000000ff;
    header[23] = (height >> 8) &0x000000ff;
    header[24] = (height >> 16) &0x000000ff;
    header[25] = (height >> 24) &0x000000ff;
    sprintf(fname_bmp, "%s.bmp", filename);
    FILE *fp; 
    if (!(fp = fopen(fname_bmp, "wb")))
    {    
        return -1;
    }        
    fwrite(header, sizeof(unsigned char), 54, fp);
    fwrite(image, sizeof(unsigned char), (size_t)(long)(xsize * 3 + FillingByte) * ysize, fp);
    fclose(fp);
    return 0;
}

unsigned char *array_to_raw_image(const int xsize, const int ysize, const RGB* const input_data)
{
    unsigned char FillingByte;
    FillingByte = bmp_filling_byte_calc(xsize);
    unsigned char *output;
    output = malloc(sizeof *output * (xsize * 3 + FillingByte) * ysize);
    if(output == NULL)
    {    
        printf("Memory allocation error!");
        return NULL;
    }
    for(int y = 0;y < ysize;y++)
    {
        for(int x = 0;x < (xsize * 3 + FillingByte);x++)
        {
            output[y * (xsize * 3 + FillingByte) + x] = 0;
        }
    }
    for(int y = 0;y<ysize;y++)
    {
        for(int x = 0;x<xsize;x++)
        {
            for (int color = 0; color < 3; color++) {
                output[3 * (y * xsize + x) + y * FillingByte + (2 - color)]
                = input_data[y*xsize + x].channels[color];
            }
        }
    }
    return output;
}

unsigned char bmp_filling_byte_calc(const unsigned int xsize)
{
    unsigned char filling_bytes;
    filling_bytes = ( xsize % 4);
    return filling_bytes;
}


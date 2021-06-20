/* Develop by Jimmy Hu */

#include "basic_functions.h"

MONOIMAGE CreateMonoImage(const unsigned int sizex, const unsigned int sizey)
{
    MONOIMAGE output;
    output.XSIZE = sizex;
    output.YSIZE = sizey;
    output.IMAGE_DATA = malloc(sizeof *output.IMAGE_DATA * sizex * sizey);
    if(output.IMAGE_DATA == NULL)
    {    
        printf(stderr, "Memory allocation error!");
        return output;
    }
    return output;
}

void DeleteMonoImage(MONOIMAGE image)
{
    free(image.IMAGE_DATA);
    return;
}

MONOIMAGE GetPlaneR(const RGBIMAGE image)
{
    MONOIMAGE output = CreateMonoImage(image.XSIZE, image.YSIZE);
    for (size_t y = 0; y < image.YSIZE; y++)
    {
        for (size_t x = 0; x < image.XSIZE; x++)
        {
            output.IMAGE_DATA[GetMonoImageIndex(x, y, output)] = 
                image.IMAGE_DATA[GetRGBImageIndex(x, y, image)].channels[0];
        }
    }
    return output;
}

MONOIMAGE GetPlaneG(const RGBIMAGE image)
{
    MONOIMAGE output = CreateMonoImage(image.XSIZE, image.YSIZE);
    for (size_t y = 0; y < image.YSIZE; y++)
    {
        for (size_t x = 0; x < image.XSIZE; x++)
        {
            output.IMAGE_DATA[GetMonoImageIndex(x, y, output)] = 
                image.IMAGE_DATA[GetRGBImageIndex(x, y, image)].channels[1];
        }
    }
    return output;
}

MONOIMAGE GetPlaneB(const RGBIMAGE image)
{
    MONOIMAGE output = CreateMonoImage(image.XSIZE, image.YSIZE);
    for (size_t y = 0; y < image.YSIZE; y++)
    {
        for (size_t x = 0; x < image.XSIZE; x++)
        {
            output.IMAGE_DATA[GetMonoImageIndex(x, y, output)] = 
                image.IMAGE_DATA[GetRGBImageIndex(x, y, image)].channels[2];
        }
    }
    return output;
}

RGBIMAGE CreateRGBImage(const unsigned int sizex, const unsigned int sizey)
{
    RGBIMAGE output;
    output.XSIZE = sizex;
    output.YSIZE = sizey;
    output.IMAGE_DATA = malloc(sizeof *output.IMAGE_DATA * sizex * sizey);
    if(output.IMAGE_DATA == NULL)
    {    
        printf(stderr, "Memory allocation error!");
        return output;
    }
    return output;
}

RGBIMAGE CreateRGBImageFromMonoImages(const unsigned int sizex, const unsigned int sizey, MONOIMAGE R, MONOIMAGE G, MONOIMAGE B)
{
    RGBIMAGE output;
    output.XSIZE = sizex;
    output.YSIZE = sizey;
    output.IMAGE_DATA = malloc(sizeof *output.IMAGE_DATA * sizex * sizey);
    if (output.IMAGE_DATA == NULL)
    {    
        printf(stderr, "Memory allocation error!");
        return output;
    }
    if ((R.XSIZE != G.XSIZE) ||
        (G.XSIZE != B.XSIZE) ||
        (R.XSIZE != B.XSIZE) ||
        (R.YSIZE != G.YSIZE) ||
        (G.YSIZE != B.YSIZE) ||
        (R.YSIZE != B.YSIZE))
    {
        printf(stderr, "Input size inequal!");
        return output;
    }
    for (size_t y = 0; y < R.YSIZE; y++)
    {
        for (size_t x = 0; x < R.XSIZE; x++)
        {
            output.IMAGE_DATA[GetRGBImageIndex(x, y, output)].channels[0] = R.IMAGE_DATA[GetMonoImageIndex(x, y, R)];
            output.IMAGE_DATA[GetRGBImageIndex(x, y, output)].channels[1] = G.IMAGE_DATA[GetMonoImageIndex(x, y, G)];
            output.IMAGE_DATA[GetRGBImageIndex(x, y, output)].channels[2] = B.IMAGE_DATA[GetMonoImageIndex(x, y, B)];
        }
    }
    return output;
}

void DeleteRGBImage(RGBIMAGE image)
{
    free(image.IMAGE_DATA);
    return;
}

size_t GetMonoImageIndex(const size_t x, const size_t y, const MONOIMAGE image)
{
    return y * image.XSIZE + x;
}

size_t GetRGBImageIndex(const size_t x, const size_t y, const RGBIMAGE image)
{
    return y * image.XSIZE + x;
}

size_t clip(const size_t input, const size_t lowerbound, const size_t upperbound)
{
    if (input < lowerbound)
    {
        return lowerbound;
    }
    if (input > upperbound)
    {
        return upperbound;
    }
    return input;
}

float clip_float(const float input, const float lowerbound, const float upperbound)
{
    if (input < lowerbound)
    {
        return lowerbound;
    }
    if (input > upperbound)
    {
        return upperbound;
    }
    return input;
}
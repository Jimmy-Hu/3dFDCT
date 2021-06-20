/* Develop by Jimmy Hu */

#include "basic_functions.h"

MONOIMAGE CreateMonoImage(const unsigned int sizex, const unsigned int sizey)
{
    MONOIMAGE output;
    output.XSIZE = sizex;
    output.YSIZE = sizey;
    output.IMAGE_DATA = malloc(sizeof *output.IMAGE_DATA * sizex * sizey);
}

void DeleteMonoImage(MONOIMAGE image)
{
    free(image.IMAGE_DATA);
    return;
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
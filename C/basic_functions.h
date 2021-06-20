/* Develop by Jimmy Hu */

#ifndef BASIC_FUNCTIONS_H
#define BASIC_FUNCTIONS_H

#include "base.h"
#include "imageio.h"

MONOIMAGE CreateMonoImage(const unsigned int, const unsigned int);

void DeleteMonoImage(MONOIMAGE);

MONOIMAGE GetPlaneR(const RGBIMAGE);

MONOIMAGE GetPlaneG(const RGBIMAGE);

MONOIMAGE GetPlaneB(const RGBIMAGE);

RGBIMAGE CreateRGBImage(const unsigned int, const unsigned int);

RGBIMAGE CreateRGBImageFromMonoImages(const unsigned int, const unsigned int, MONOIMAGE, MONOIMAGE, MONOIMAGE);

void DeleteRGBImage(RGBIMAGE);

size_t GetMonoImageIndex(const size_t, const size_t, const MONOIMAGE);

size_t GetRGBImageIndex(const size_t, const size_t, const RGBIMAGE);

size_t clip(const size_t, const size_t, const size_t);

float clip_float(const float, const float, const float);

#endif
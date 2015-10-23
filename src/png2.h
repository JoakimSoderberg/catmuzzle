#ifndef PNG2_H
#define PNG2_H

#include <stdio.h>
#include "lodepng.h"

static unsigned char * read_png_file(char * filename,
                                     unsigned int * width,
                                     unsigned int * height,
                                     unsigned int * bitsperpixel)
{
    unsigned error;
	unsigned char* image;
	unsigned w, h;
	error = lodepng_decode24_file(&image, &w, &h, filename);
	if (error) printf("read_png_file: error %u: %s\n", error, lodepng_error_text(error));

    *width = w;
    *height = h;
    *bitsperpixel=24;
    return image;
}

#endif

/*
   catmuzzle - A cat muzzle detector
   Copyright (C) 2015 Bob Mottram <bob@robotics.uk.to>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

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

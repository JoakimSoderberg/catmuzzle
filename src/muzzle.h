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

#ifndef MUZZLE_H
#define MUZZLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <omp.h>

void muzzle_profile(unsigned char * img,
                    int image_width, int image_height, int bytesperpixel,
                    int samples, float profile[]);

void muzzle_csv(unsigned char * img,
                int image_width, int image_height, int bytesperpixel,
                int positive);

#endif

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

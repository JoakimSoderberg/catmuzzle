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

#include "muzzle.h"

const int border_percent = 10;

void muzzle_smooth(int samples, float profile[])
{
    int i;
    float last = 0;

    for (i = 0; i < samples; i++) {
        if ((profile[i] == 0) || (profile[i] == 1)) {
            profile[i] = last;
            continue;
        }
        if (profile[i] > 0) {
            last = profile[i];
        }
    }
}

/* normalise for translational invariance */
void muzzle_normalise(int samples, float profile[])
{
    int i;
    float min=0,max=0;

    for (i = 0; i < samples; i++) {
        if (i == 0) {
            min = profile[i];
            max = min;
            continue;
        }
        if (profile[i] > max) max = profile[i];
        if (profile[i] < min) min = profile[i];
    }
    if (max == min) return;
    for (i = 0; i < samples; i++) {
        profile[i] = (profile[i] - min)/(max - min);
    }
    muzzle_smooth(samples, profile);
}

/* for a number of horizontal samples find the maximum edge response */
void muzzle_profile_horizontal(unsigned char * img,
                               int image_width, int image_height, int bytesperpixel,
                               int samples, float profile[])
{
    int s, x, xx, y;
    int border_pixels = image_width * border_percent / 100;
    int diff, max_diff;

    for (s = 0; s < samples; s++) {
        y = s * image_height / samples;
        max_diff = 0;
        profile[s] = 0;
        for (x = border_pixels; x < image_width-border_pixels; x++) {
            diff = 0;
            for (xx = x - border_pixels; xx < x; xx++) {
                diff += img[(y*image_width + xx)*bytesperpixel] * img[(y*image_width + xx)*bytesperpixel];
            }
            for (xx = x; xx < x + border_pixels; xx++) {
                diff -= img[(y*image_width + xx)*bytesperpixel] * img[(y*image_width + xx)*bytesperpixel];
            }
            if (diff < 0) diff = -diff;
            if (diff > max_diff) {
                max_diff = diff;
                profile[s] = (float)x/(float)image_width;
            }
        }
    }
    muzzle_normalise(samples, profile);
}

/* gather samples starting from the bottom of the image moving diagonally rightwards */
static void muzzle_profile_diagonal_right(unsigned char * img,
                                          int image_width, int image_height, int bytesperpixel,
                                          int samples, float profile[])
{
    int s, x, y, xx, ctr;
    int border_pixels;
    int diff, max_diff;
    unsigned char data[2048];

    for (s = 0; s < samples; s++) {
        x = s * image_width / samples;
        max_diff = 0;
        profile[s] = 0;
        xx = x;
        ctr = 0;
        /* gather diagonal data */
        for (y = image_height-1; y > 0; y--, xx++, ctr++) {
            if (xx >= image_width-1) break;
            if (ctr >= 2048) break;
            data[ctr] = img[(y*image_width + xx)*bytesperpixel];
        }
        if (ctr > 5) {
            border_pixels = ctr * border_percent / 100;
            for (y = border_pixels; y < ctr-border_pixels; y++) {
                diff = 0;
                for (xx = y - border_pixels; xx < y; xx++) {
                    diff += data[xx];
                }
                for (xx = y; xx < y + border_pixels; xx++) {
                    diff -= data[xx];
                }
                if (diff < 0) diff = -diff;
                if (diff > max_diff) {
                    max_diff = diff;
                    profile[s] = (float)y/(float)ctr;
                }
            }
        }
    }

    muzzle_normalise(samples, profile);
}

/* gather samples starting from the bottom of the image moving diagonally leftwards */
static void muzzle_profile_diagonal_left(unsigned char * img,
                                         int image_width, int image_height, int bytesperpixel,
                                         int samples, float profile[])
{
    int s, x, y, xx, ctr;
    int border_pixels;
    int diff, max_diff;
    unsigned char data[2048];

    for (s = 0; s < samples; s++) {
        x = s * image_width / samples;
        max_diff = 0;
        profile[s] = 0;
        xx = x;
        ctr = 0;
        /* gather diagonal data */
        for (y = image_height-1; y > 0; y--, xx--, ctr++) {
            if (xx < 1) break;
            if (ctr >= 2048) break;
            data[ctr] = img[(y*image_width + xx)*bytesperpixel];
        }
        if (ctr > 5) {
            border_pixels = ctr * border_percent / 100;
            for (y = border_pixels; y < ctr-border_pixels; y++) {
                diff = 0;
                for (xx = y - border_pixels; xx < y; xx++) {
                    diff += data[xx];
                }
                for (xx = y; xx < y + border_pixels; xx++) {
                    diff -= data[xx];
                }
                if (diff < 0) diff = -diff;
                if (diff > max_diff) {
                    max_diff = diff;
                    profile[s] = (float)y/(float)ctr;
                }
            }
        }
    }

    muzzle_normalise(samples, profile);
}

/* obtains a profile for the given cat image */
void muzzle_profile(unsigned char * img,
                    int image_width, int image_height, int bytesperpixel,
                    int samples, float profile[])
{
    int samples_per_axis = samples/3;

    muzzle_profile_horizontal(img, image_width, image_height, bytesperpixel,
                              samples_per_axis, profile);

    muzzle_profile_diagonal_right(img, image_width, image_height, bytesperpixel,
                                  samples_per_axis, &profile[samples_per_axis]);

    muzzle_profile_diagonal_left(img, image_width, image_height, bytesperpixel,
                                 samples_per_axis, &profile[samples_per_axis*2]);
}

/* print the profile for the given cat picture in csv format to stdout */
void muzzle_csv(unsigned char * img,
                int image_width, int image_height, int bytesperpixel,
                int positive)
{
    int i, samples = 256*3;
    float profile[256*3];

    muzzle_profile(img, image_width, image_height, bytesperpixel, samples, profile);
    for (i = 0; i < samples; i++) {
        printf("%.4f,", profile[i]);
    }
    printf("%d\n", positive);
}

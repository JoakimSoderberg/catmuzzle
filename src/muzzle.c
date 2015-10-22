#include "muzzle.h"

const int border_percent = 5;

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
}

void muzzle_profile_horizontal(unsigned char * img, int image_width, int image_height, int bytesperpixel,
							   int samples, float profile[])
{
	int s, x, xx, y;
	int border_pixels = image_width * percent / 100;
	int diff, max_diff;

	for (s = 0; s < samples; s++) {
		y = s * image_height / samples;
		max_diff = 0;
		profile[s] = 0;
		for (x = border_pixels; x < image_width-border_pixels; x++) {
			diff = 0;
			for (xx = x - border_pixels; xx < x; xx++) {
				diff += img[(y*image_width + xx)*bytesperpixel];
			}
			for (xx = x; xx < x + border_pixels; xx++) {
				diff -= img[(y*image_width + xx)*bytesperpixel];
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

void muzzle_profile_diagonal_left(unsigned char * img, int image_width, int image_height, int bytesperpixel,
								  int samples, float profile[])
{
	int s, x, yy, y;
	int border_pixels = image_height * percent / 100;
	int diff, max_diff;

	for (s = 0; s < samples; s++) {
		x = s * image_width / samples;
		max_diff = 0;
		profile[s] = 0;
		for (y = image_height-1-border_pixels; y > border_pixels; y--) {
			diff = 0;
			for (yy = x - border_pixels; xx < x; xx++) {
				diff += img[(y*image_width + xx)*bytesperpixel];
			}
			for (xx = x; xx < x + border_pixels; xx++) {
				diff -= img[(y*image_width + xx)*bytesperpixel];
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

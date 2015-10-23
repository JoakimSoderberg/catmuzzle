#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "png2.h"
#include "muzzle.h"

int main(int argc, char* argv[])
{
    char * filename = NULL;
    char output_filename[255];
    unsigned int image_width=0;
    unsigned int image_height=0;
    unsigned int image_bitsperpixel=0;
    unsigned char * image_data = NULL;
	int i, positive = 0;

    sprintf((char*)output_filename,"%s","result.png");

    for (i=1;i<argc;i++) {
        if ((strcmp(argv[i],"-f")==0) ||
            (strcmp(argv[i],"--filename")==0)) {
            filename = argv[i+1];
			i++;
        }
        if ((strcmp(argv[i],"-p")==0) ||
            (strcmp(argv[i],"--positive")==0)) {
            positive = 1;
        }
        if ((strcmp(argv[i],"-n")==0) ||
            (strcmp(argv[i],"--negative")==0)) {
            positive = 0;
        }
    }

    /* was a file specified */
    if (filename == NULL) {
        printf("No image file specified\n");
        return 0;
    }

    image_data = read_png_file(filename, &image_width, &image_height, &image_bitsperpixel);
    if (image_data == NULL) {
        printf("Couldn't load image %s\n", filename);
        return 0;
    }
    if ((image_width == 0) || (image_height==0)) {
        printf("Couldn't load image size %dx%d\n", image_width, image_height);
        return 0;
    }
    if (image_bitsperpixel == 0) {
        printf("Couldn't load image depth\n");
        return 0;
    }

	muzzle_csv(image_data, image_width, image_height, image_bitsperpixel/8, positive);

    /* free memory */
    free(image_data);
    return 0;
}

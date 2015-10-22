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

    sprintf((char*)output_filename,"%s","result.png");

    for (i=1;i<argc;i+=2) {
        if ((strcmp(argv[i],"-f")==0) ||
            (strcmp(argv[i],"--filename")==0)) {
            filename = argv[i+1];
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

    printf("Image: %s\n", filename);
    printf("Resolution: %dx%d\n", image_width, image_height);
    printf("Depth: %d\n", image_bitsperpixel);

    /* save the image */
    write_png_file(output_filename, image_width, image_height, 24, image_data);

    /* free memory */
    free(image_data);

    printf("Ended Successfully\n");
    return 0;
}

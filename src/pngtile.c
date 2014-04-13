#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <png.h>

#include "astro_math.h"
#include "core_math.h"

#define IMG_W 256
#define IMG_H 256

int main(int argc, char *argv[])
{
	png_image img;
	memset(&img, '\0', sizeof(png_image));

	img.version = PNG_IMAGE_VERSION;
	img.width = IMG_W;
	img.height = IMG_H;
	img.format = PNG_FORMAT_RGB;
	img.flags = 0;
	img.opaque = NULL;
	img.colormap_entries = 256;

    double jdate = 256;
    struct rgb img_data[IMG_W][IMG_H];
    memset(&img_data, '\0', sizeof(struct rgb));

    if (argc < 4) {
		printf("usage: grav z x y\n");
		return EXIT_FAILURE;
    }

    int z = atoi(argv[1]);
    int x = atoi(argv[2]);
    int y = atoi(argv[3]);

    colour(img_data, x, y, z, jdate);

 //   printf("z: %d, x: %d, y: %d\n", z, x, y);

	png_image_write_to_stdio(&img, stdout, 0, &img_data, 0, NULL);

	png_image_free(&img);

	return EXIT_SUCCESS;
}

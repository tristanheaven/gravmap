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

static double unixtojd(const int t)
{
	return (t / 86400.0 ) + 2440587.5;
}

int main(int argc, char *argv[])
{
	if (argc != 5) {
		printf("usage: gravmap z x y t\n");
		return EXIT_FAILURE;
	}

	const int z = atoi(argv[1]);
	const int x = atoi(argv[2]);
	const int y = atoi(argv[3]);
	const int t = atoi(argv[4]);

	png_image img;
	memset(&img, '\0', sizeof(img));

	img.version = PNG_IMAGE_VERSION;
	img.width = IMG_W;
	img.height = IMG_H;
	img.format = PNG_FORMAT_RGB;
	img.flags = 0;
	img.opaque = NULL;
	img.colormap_entries = 256;

	struct rgb img_data[IMG_W][IMG_H];
	memset(&img_data, '\0', sizeof(img_data));

	colour(img_data, x, y, z, unixtojd(t));

	png_image_write_to_stdio(&img, stdout, 0, &img_data, 0, NULL);
	png_image_free(&img);

	return EXIT_SUCCESS;
}

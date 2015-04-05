#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <png.h>
#include <time.h>

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
		puts("usage: gravmap z x y t");
		puts("z: map zoom level");
		puts("x: x tile position");
		puts("y: y tile position");
		puts("t: time in seconds from 1970");

		return EXIT_FAILURE;
	}

	const uint8_t z = atoi(argv[1]);
	const uint8_t x = atoi(argv[2]);
	const uint8_t y = atoi(argv[3]);
	const time_t t = atoi(argv[4]);

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

	colour(img_data, x, y, z, unixtojd(t), t % DAY_IN_SECONDS);

	png_image_write_to_stdio(&img, stdout, 0, &img_data, 0, NULL);
	png_image_free(&img);

	return EXIT_SUCCESS;
}

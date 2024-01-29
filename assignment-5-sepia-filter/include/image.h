#pragma once

#include <stdbool.h>
#include <stdint.h>
#define PIXEL_SIZE sizeof(struct pixel)


struct pixel { uint8_t b, g, r; };

struct image {
  uint64_t width, height;
  struct pixel* data;
};

bool image_init(struct image* img, uint64_t width, uint64_t height);
void image_destroy(struct image* image);

void copy_img(struct image const in, struct image* out);


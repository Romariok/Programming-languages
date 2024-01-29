#include "../include/image.h"
#include <stdint.h>
#include <stdlib.h>

bool image_init(struct image* img, uint64_t width, uint64_t height)
{
  *img = (struct image){
      .width = width,
      .height = height,
      .data = malloc(PIXEL_SIZE * width * height)};

  return img->data != NULL;
}

void image_destroy(struct image *image)
{
  if (!image || !image->data)
    return;
  free(image->data);
  image->data = NULL;
}

void copy_img(struct image const in, struct image* out){
  image_init(out, in.width, in.height);

  for (uint64_t i = 0; i < in.height; i++)
  {
    for (uint64_t j = 0; j < in.width; j++)
    {
      struct pixel *curr_pixel = in.data + (i * in.width) + j;
      out->data[(i * in.width) + j] = *curr_pixel;
    }
  }
}
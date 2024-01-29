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

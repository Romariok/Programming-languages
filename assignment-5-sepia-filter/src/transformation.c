#include "transformation.h"
#include <stdio.h>
#include <string.h>

void sepia_image(struct image const *img);

struct image sepia_asm(struct image const in)
{
   struct image out = {0};
   copy_img(in, &out);
   sepia_image(&out);
   return out;
}


struct image sepia(struct image const in)
{
   struct image out = {0};
   copy_img(in, &out);
   if (out.data == NULL)
      return in;

   for (uint64_t i = 0; i < out.height; i++)
   {
      for (uint64_t j = 0; j < out.width; j++)
      {
         struct pixel *curr_pixel = out.data + (i * out.width) + j;
         uint64_t new_r = (0.393 * curr_pixel->r + 0.769 * curr_pixel->g + 0.189 * curr_pixel->b);
         uint64_t new_g = (0.349 * curr_pixel->r + 0.686 * curr_pixel->g + 0.168 * curr_pixel->b);
         uint64_t new_b = (0.272 * curr_pixel->r + 0.534 * curr_pixel->g + 0.131 * curr_pixel->b);
         curr_pixel->r = new_r > 0xFF ? 0xFF : new_r;
         curr_pixel->g = new_g > 0xFF ? 0xFF : new_g;
         curr_pixel->b = new_b > 0xFF ? 0xFF : new_b;
      }
   }
   return out;
}

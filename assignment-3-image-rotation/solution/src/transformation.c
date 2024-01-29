#include "transformation.h"
#include <stdio.h>
#include <string.h>

struct image rotate(struct image const in, char *const angle)
{

   if (strcmp(angle, "0") == 0)
   {
      return in;
   }
   else
   {
      struct image out = {0};
      uint64_t height = in.width;
      uint64_t width = in.height;
      if (strcmp(angle, "180") == 0 || strcmp(angle, "-180") == 0)
      {
         height = in.height;
         width = in.width;
      }
      if (!image_init(&out, width, height))
         return in;
      for (uint64_t i = 0; i < height; i++)
      {
         for (uint64_t j = 0; j < width; j++)
         {
            uint64_t in_index = 0;
            uint64_t out_index = i * out.width + j;
            if (strcmp(angle, "90") == 0 || strcmp(angle, "-270") == 0)
            {
               in_index = (in.height - j - 1) * in.width + i;
            }
            else if (strcmp(angle, "-90") == 0 || strcmp(angle, "270") == 0)
            {
               in_index = j * in.width + (in.width - i - 1);
            }
            else
            {
               in_index = (in.height - i - 1) * in.width + (in.width - j - 1);
            }

            out.data[out_index] = in.data[in_index];
         }
      }
      return out;
   }
}

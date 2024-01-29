#include "../include/bmp.h"
#include <malloc.h>
#include <stdio.h>


#define BF_RESERVED 0
#define BI_SIZE 40
#define BI_PLANES 1
#define BI_BIT_COUNT 24
#define BI_COMPRESSION 0
#define BI_XPELS_PER_METER 1
#define BI_YPELS_PER_METER 1
#define BI_CLR_USED 0
#define BI_CLR_IMPORTANT 0
#define BMP_SIGNATURE 0x4D42
#define BMP_HEADER_SIZE sizeof(struct bmp_header)

#pragma pack(push, 1)
struct bmp_header
{
   uint16_t bfType;
   uint32_t bfileSize;
   uint32_t bfReserved;
   uint32_t bOffBits;
   uint32_t biSize;
   uint32_t biWidth;
   uint32_t biHeight;
   uint16_t biPlanes;
   uint16_t biBitCount;
   uint32_t biCompression;
   uint32_t biSizeImage;
   uint32_t biXPelsPerMeter;
   uint32_t biYPelsPerMeter;
   uint32_t biClrUsed;
   uint32_t biClrImportant;
} ;
#pragma pack(pop)
static uint16_t calculate_padding(uint64_t const width)
{
   return (4 - (width * PIXEL_SIZE) % 4) % 4;
}

enum read_status from_bmp(FILE *in, struct image *img)
{
   struct bmp_header *header = (struct bmp_header *)malloc(BMP_HEADER_SIZE);
   if (header == NULL)
      return READ_ERROR;

   if (fread(header, BMP_HEADER_SIZE, 1, in) != 1)
   {
      free(header);
      return READ_INVALID_HEADER;
   }
   if (header->bfType != BMP_SIGNATURE)
   {
      return READ_INVALID_SIGNATURE;
   }

   

   if (!image_init(img, header->biWidth, header->biHeight)) return READ_MEMORY_ERROR;

   uint16_t padding = calculate_padding(img->width);

   fseek(in, header->bOffBits, SEEK_SET);
   for (uint32_t i = 0; i < img->height; i++)
   {
      if (!fread(&img->data[(img->height - i - 1) * img->width], PIXEL_SIZE * img->width, 1, in))
      {
         free(header);
         image_destroy(img);
         return READ_INVALID_BITS;
      }
      fseek(in, padding, SEEK_CUR);
   }
   free(header);
   return READ_OK;
}

enum write_status to_bmp(FILE *out, struct image const *img)
{
   struct bmp_header header = {0};

   header.bfType = BMP_SIGNATURE;
   header.bfileSize = BMP_HEADER_SIZE + img->width * img->height * PIXEL_SIZE;
   header.bfReserved = BF_RESERVED;
   header.bOffBits = BMP_HEADER_SIZE;
   header.biSize = BI_SIZE;
   header.biWidth = img->width;
   header.biHeight = img->height;
   header.biPlanes = BI_PLANES;
   header.biBitCount = BI_BIT_COUNT;
   header.biCompression = BI_COMPRESSION;
   header.biSizeImage = (img->width  * PIXEL_SIZE + calculate_padding(img->width)) * img->height;
   header.biXPelsPerMeter = BI_XPELS_PER_METER;
   header.biYPelsPerMeter = BI_YPELS_PER_METER;
   header.biClrUsed = BI_CLR_USED;
   header.biClrImportant = BI_CLR_IMPORTANT;

   fwrite(&header, BMP_HEADER_SIZE, 1, out);

   uint32_t padding = calculate_padding(img->width);

   for (uint64_t i = 0; i < img->height; i++)
   {
      if (fwrite(&img->data[(img->height - i - 1) * img->width], PIXEL_SIZE * img->width, 1, out) != 1)
         return WRITE_ERROR;

      if (fwrite(&padding, 1, padding, out) != padding)
         return WRITE_ERROR;
   }

   return WRITE_OK;
}

void out_read_status(enum read_status const status)
{
   switch (status)
   {
   case READ_INVALID_HEADER:
      fprintf(stderr, "Invalid header\n");
      break;
   case READ_INVALID_SIGNATURE:
      fprintf(stderr, "Invalid signature\n");
      break;
   case READ_MEMORY_ERROR:
      fprintf(stderr, "Memory error\n");
      break;
   case READ_OK:
      fprintf(stdout, "File read successfully\n");
      break;
   default:
      break;
   }
}
void out_write_status(enum write_status const status)
{
   switch (status)
   {
   case WRITE_OK:
      fprintf(stdout, "File written successfully\n");
      break;
   case WRITE_ERROR:
      fprintf(stderr, "File write error\n");
      break;
   default:
      break;
   }
}

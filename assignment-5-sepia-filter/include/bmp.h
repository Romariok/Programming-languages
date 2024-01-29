#pragma once

#include "image.h"
#include  <stdint.h>
#include <stdio.h>


enum read_status  {
  READ_OK = 0,
  READ_INVALID_SIGNATURE,
  READ_INVALID_BITS,
  READ_INVALID_HEADER,
  READ_ERROR,
  READ_MEMORY_ERROR
  };

enum read_status from_bmp( FILE* in, struct image* img );

/*  serializer   */
enum  write_status  {
  WRITE_OK = 0,
  WRITE_ERROR
};

enum write_status to_bmp( FILE* out, struct image const* img );
void out_read_status(enum read_status const status);
void out_write_status(enum write_status const status);

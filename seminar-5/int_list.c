/* int_list.c */

#include <stdint.h>

struct list_int {
  int64_t value;
  struct list_int* next;
};

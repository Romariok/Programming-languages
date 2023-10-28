/* double_list.c */

#include <stdint.h>

struct list_double {
  double value;
  struct list_double* next;
};

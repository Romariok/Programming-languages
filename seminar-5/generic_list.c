/* generic_list.c */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

void error(const char *s)
{
  fprintf(stderr, "%s", s);
  abort();
}

void int64_t_print(int64_t i)
{
  printf("%" PRId64 " ", i);
}

void double_print(double d)
{
  printf("%lf ", d);
}
void newline_print() { puts(""); }

#define DEFINE_LIST(type)                                               \
  struct list_##type                                                    \
  {                                                                     \
    type value;                                                         \
    struct list_##type *next;                                           \
  };                                                                    \
  void list_##type##_push(struct list_##type *list, type value)         \
  {                                                                     \
    struct list_##type *const new = malloc(sizeof(struct list_##type)); \
    while (list->next != 0)                                             \
      list = list->next;                                                \
    new->value = value;                                                 \
    new->next = 0;                                                      \
    list->next = new;                                                   \
  }                                                                     \
  void list_##type##_print(struct list_##type *list)                    \
  {                                                                     \
    while (list != 0)                                                   \
    {                                                                   \
      type##_print(list->value);                                        \
      list = list->next;                                                \
    }                                                                   \
  }

DEFINE_LIST(int64_t)
DEFINE_LIST(double)

struct list_int64_t *create_int_node(int64_t x)
{
  struct list_int64_t *node = malloc(sizeof(struct list_int64_t));
  node->value = x;
  return node;
}

struct list_double *create_double_node(double x)
{
  struct list_double *node = malloc(sizeof(struct list_double));
  node->value = x;
  return node;
}
#define list_print(x)                          \
  _Generic((x),                                \
      struct list_int64_t*: list_int64_t_print(x), \
      struct list_double*: list_double_print(x),   \
      default: error("Unsupported operation"))

int main()
{
  struct list_int64_t *list_int = create_int_node(4141);
  list_int->next = create_int_node(0);
  list_int->next->next = create_int_node(711);
  // list_int64_t_print(list_int);
  list_print(list_int); //GENERIC

  newline_print();

  struct list_double *list_double1 = create_double_node(1151515.0);
  list_double1->next = create_double_node(51.1151);
  list_double1->next->next = create_double_node(55.55);
  list_double1->next->next->next = create_double_node(0.0);
  list_double1->next->next->next->next = create_double_node(14841.54);
  // list_double_print(list_double1);
  list_print(list_double1); //GENERIC

  newline_print();

  struct list_double *list_double2 = create_double_node(51.2);
  list_double2->next = create_double_node(91891.111);

  // list_double_print(list_double2);
    list_print(list_double2); //GENERIC
}
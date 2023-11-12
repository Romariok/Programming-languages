#include "array.h"
#include <malloc.h>



struct array newArray(size_t capacity)
{
   return (struct array) {.data = malloc(sizeof(int64_t) * capacity), .count = 0, .capacity = capacity};
}



void appendArray(struct array *a, struct array *b)
{
   if (a->count + b->count > a->capacity)
   {
      a->data = realloc(a->data, sizeof(int64_t) * (a->capacity + b->count));
      a->capacity = a->capacity + b->count;
   }
   for (size_t i = 0; i < b->count; i++)
   {
      a->data[a->count++] = b->data[i];
   }
}

void append(struct array *a, int64_t value)
{
   if (a->count == a->capacity)
   {
      a->data = realloc(a->data, sizeof(int64_t) * a->capacity * 2);
      a->capacity = a->capacity * 2;
   }
   a->data[a->count++] = value;
}

size_t getCapacity(struct array *a)
{
   return a->capacity;
}
size_t getCount(struct array *a)
{
   return a->count;
}
int64_t getByIndex(struct array *a, size_t index)
{
   return a->data[index];
}

void freeUnusedMemory(struct array *a)
{
   a->data = realloc(a->data, sizeof(int64_t) * a->count);
   a->capacity = a->count;
}
void setCapacity(struct array *a, size_t capacity)
{
   a->data = realloc(a->data, sizeof(int64_t) * capacity);
}

void freeArray(struct array *a)
{
   free(a->data);
   free(a);
}

void printArray(struct array *a, FILE *f){
   for (size_t i = 0; i < a->count; i++){
      fprintf(f, "%" PRId64 " ", a->data[i]);
   }
}
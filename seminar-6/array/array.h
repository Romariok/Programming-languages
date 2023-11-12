#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

struct array
{
   int64_t *data;
   size_t count;
   size_t capacity;
};



int64_t getByIndex(struct array *a, size_t index);
void append(struct array *a, int64_t value);
void appendArray(struct array *a, struct array *b);

size_t getCapacity(struct array *a);
size_t getCount(struct array *a);

void freeUnusedMemory(struct array *a);
void setCapacity(struct array *a, size_t capacity);

void freeArray(struct array *a);

struct array newArray(size_t capacity);

void printArray(struct array *a, FILE *f);
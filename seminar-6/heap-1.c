/* heap-1.c */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HEAP_BLOCKS 16
#define BLOCK_CAPACITY 1024

enum block_status
{
  BLK_FREE = 0,
  BLK_ONE,
  BLK_FIRST,
  BLK_CONT,
  BLK_LAST
};

struct heap
{
  struct block
  {
    char contents[BLOCK_CAPACITY];
  } blocks[HEAP_BLOCKS];
  enum block_status status[HEAP_BLOCKS];
} global_heap = {0};

struct block_id
{
  size_t value;
  bool valid;
  struct heap *heap;
};

struct block_id block_id_new(size_t value, struct heap *from)
{
  return (struct block_id){.valid = true, .value = value, .heap = from};
}
struct block_id block_id_invalid()
{
  return (struct block_id){.valid = false};
}

bool block_id_is_valid(struct block_id bid)
{
  return bid.valid && bid.value < HEAP_BLOCKS;
}

/* Find block */

bool block_is_free(struct block_id bid)
{
  if (!block_id_is_valid(bid))
    return false;
  return bid.heap->status[bid.value] == BLK_FREE;
}

/* Allocate */

struct block_id block_allocate(struct heap *heap, size_t size)
{
  // Required only one block
  if (size <= BLOCK_CAPACITY)
  {
    for (size_t i = 0; i < HEAP_BLOCKS; i++)
    {
      if (heap->status[i] == BLK_FREE)
      {
        heap->status[i] = BLK_ONE;
        return block_id_new(i, heap);
      }
    }
  }
  else
  {

    uint64_t count = (size + BLOCK_CAPACITY - 1) / BLOCK_CAPACITY; // number of blocks
    for (size_t i = 0; i < HEAP_BLOCKS - 1; i++)                   // validation of situation, where blocks can be allocated next to each other
    {
      if (heap->status[i] == BLK_FREE)
      {
        bool capacity_found = true;
        for (size_t j = i + 1; j < i + count; j++) // validation of capacity
        {
          if (heap->status[j] != BLK_FREE)
          {
            capacity_found = false;
            break;
          }
        }
        if (capacity_found) // We can put blocks next to each other
        {
          heap->status[i] = BLK_FIRST;
          heap->status[i + count - 1] = BLK_LAST;
          for (size_t j = i + 1; j < i + count - 1; j++)
          {
            heap->status[j] = BLK_CONT;
          }
          return block_id_new(i, heap);
        }
      }
    }

    return block_id_invalid();
  }
}
/* Free */
void block_free(struct block_id bid)
{
  if (!block_id_is_valid(bid) || bid.heap->status[bid.value] == BLK_FREE)
    return;
  if (bid.heap->status[bid.value] == BLK_ONE)
  {
    bid.heap->status[bid.value] = BLK_FREE;
    return;
  }
  size_t tmp = bid.value;
  while (bid.heap->status[tmp] != BLK_LAST)
  {
    bid.heap->status[tmp] = BLK_FREE;
    tmp++;
  }
  bid.heap->status[tmp] = BLK_FREE;
}

/* Printer */
const char *block_repr(struct block_id b)
{
  static const char *const repr[] = {[BLK_FREE] = " .",
                                     [BLK_ONE] = " *",
                                     [BLK_FIRST] = "[=",
                                     [BLK_LAST] = "=]",
                                     [BLK_CONT] = " ="};
  if (b.valid)
    return repr[b.heap->status[b.value]];
  else
    return "INVALID";
}

void block_debug_info(struct block_id b, FILE *f)
{
  fprintf(f, "%s", block_repr(b));
}

void block_foreach_printer(struct heap *h, size_t count,
                           void printer(struct block_id, FILE *f), FILE *f)
{
  for (size_t c = 0; c < count; c++)
    printer(block_id_new(c, h), f);
}

void heap_debug_info(struct heap *h, FILE *f)
{
  block_foreach_printer(h, HEAP_BLOCKS, block_debug_info, f);
  fprintf(f, "\n");
}
/*  -------- */

int main()
{
  block_allocate(&global_heap, 1024);
  block_allocate(&global_heap, 1024);
  heap_debug_info(&global_heap, stdout); 

  block_allocate(&global_heap, 3000);
  heap_debug_info(&global_heap, stdout);

  block_free(block_id_new(1, &global_heap));
  block_free(block_id_new(0, &global_heap));
  heap_debug_info(&global_heap, stdout);

  block_allocate(&global_heap, 5000); 
  heap_debug_info(&global_heap, stdout);

  return 0;
}

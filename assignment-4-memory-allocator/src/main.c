#define _GNU_SOURCE

#include <assert.h>
#include <stdio.h>
#include <sys/mman.h>

#include "mem.h"
#include "mem_internals.h"

#define DEFAULT_HEAP_SIZE 4096

void debug(const char *fmt, ...);

void *map_pages(void const *addr, size_t length, int additional_flags)
{
   return mmap((void *)addr, length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | additional_flags, -1, 0);
}
#define get_header(mem) \
   ((struct block_header *)(((uint8_t *)(mem)) - offsetof(struct block_header, contents)))

void heap_initialization()
{
   debug("\tTest 1: HEAP INITIALIZATION\n");
   void *heap = heap_init(DEFAULT_HEAP_SIZE);
   debug("Initializaing %d bytes\n", DEFAULT_HEAP_SIZE);
   assert(heap);
   heap_term();
   debug("\tTest 1 success\n");
}

void free_one_block()
{
   debug("\n\n\tTest 2: FREE ONE BLOCK\n");

   void *heap = heap_init(DEFAULT_HEAP_SIZE);
   debug("Initializaing %d bytes\n", DEFAULT_HEAP_SIZE);
   assert(heap);

   debug("Blocks initialization...\n", 0);
   void *first_block = _malloc(100);
   void *second_block = _malloc(200);
   void *third_block = _malloc(300);

   assert(first_block);
   assert(second_block);
   assert(third_block);

   debug("\n3 blocks initialization success\n", 0);

   debug("\nFree second block\n");
   _free(second_block);
   assert(!get_header(first_block)->is_free);
   assert(get_header(second_block)->is_free);
   assert(!get_header(third_block)->is_free);
   debug("\"free\" sucсess\n");

   _free(first_block);
   _free(third_block);
   heap_term();
   debug("\tTest 2 success\n");
}

void free_many_blocks()
{
   debug("\n\n\tTest 3: FREE MANY BLOCKS\n");

   void *heap = heap_init(DEFAULT_HEAP_SIZE);
   debug("Initializaing %d bytes\n", DEFAULT_HEAP_SIZE);
   assert(heap);

   debug("Blocks initialization...\n", 0);
   void *first_block = _malloc(100);
   void *second_block = _malloc(200);
   void *third_block = _malloc(300);

   assert(first_block);
   assert(second_block);
   assert(third_block);

   debug("\n3 blocks initialization success\n", 0);

   debug("\nFree first abd third blocks\n");
   _free(first_block);
   _free(third_block);
   assert(get_header(first_block)->is_free);
   assert(!get_header(second_block)->is_free);
   assert(get_header(third_block)->is_free);
   debug("\"free\" sucсess\n");

   _free(second_block);

   heap_term();
   debug("\tTest 3 success\n");
}


void expand_region() {
    debug("\n\n\tTest 4: EXPAND REGION\n");

    struct region* heap = heap_init(0);
    assert(heap);
    debug("Heap initialized: %d bytes\n", 0);

    size_t initial_region_size = heap->size;

    debug("\nOverflow block initialization...\n", 0);
    _malloc(5 * DEFAULT_HEAP_SIZE);
    size_t expanded_region_size = heap->size;
    debug("\nblock initialization success\n", 0); 


    assert(initial_region_size < expanded_region_size);


    heap_term();
    debug("\n\tTest 4: passed!\n");
}

void expand_region_in_new_address() {
    debug("\n\n\tTest 5: EXPAND REGION IN NEW ADDRESS\n");

    debug("\nFilling memory...\n", 0);
    void* start_region = map_pages(HEAP_START, 100, MAP_FIXED);
    assert(start_region);

    debug("\nTrying to allocate in filled region...\n", 0);

    void* new_block = _malloc(1000);
    assert(new_block);
    assert(start_region != new_block);

    heap_term();
    debug("\n\tTest 5: passed!\n");
}
int main()
{
   heap_initialization();
   free_one_block();
   free_many_blocks();
   expand_region();
   expand_region_in_new_address();


   debug("\n\tSuccess!\n");
}
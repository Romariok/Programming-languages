/* fork-example-1.c */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

void *create_shared_memory(size_t size)
{
  return mmap(NULL,
              size,
              PROT_READ | PROT_WRITE,
              MAP_SHARED | MAP_ANONYMOUS,
              -1, 0);
}

int main()
{
  void *shmem = create_shared_memory(10 * sizeof(int));

  int *arr = (int *)shmem;
  for (int i = 0; i < 10; i++)
  {
    arr[i] = i;
  }

  printf("Shared memory size: %ld\n", 10 * sizeof(int));
  printf("Shared memory at: %p\n", shmem);
  int pid = fork();

  if (pid == 0)
  {
    int index, new_value;
    printf("Enter array index and new value: ");
    scanf("%d %d", &index, &new_value);
    if (index >= 0 && index < 10)
    {
      arr[index] = new_value;
    }
    exit(0);
  }
  else
  {
    printf("Child's pid is: %d\n", pid);
    wait(NULL); 
    for (int i = 0; i < 10; i++)
    {
      printf("Shared memory value at index %d: %d\n", i, arr[i]);
    }
  }
}

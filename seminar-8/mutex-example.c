/* mutex-example.c */

#include <pthread.h>
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>

uint64_t value = 0;

void* my_thread(void *_)
{
  for (int n = 0; n < 1000000; n++) 
    value += 1;
  return NULL;
}

int main(void)
{
  pthread_t t1, t2;
  pthread_create(&t1, NULL, my_thread, NULL);
  pthread_create(&t2, NULL, my_thread, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("%"PRIu64"\n", value);

  return 0;
}

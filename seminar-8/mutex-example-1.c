/* mutex-example-1.c */

#include <pthread.h>
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m;
pthread_t t1, t2;
uint64_t value = 0;

void* my_thread(void *_)
{
  for (int n = 0; n < 1000000; n++) 
  {
    pthread_mutex_lock(&m);
    value += 1;
    pthread_mutex_unlock(&m);
  }
  return NULL;
}

int main(void)
{
  pthread_mutex_init(&m, NULL);
  pthread_create(&t1, NULL, my_thread, NULL);
  pthread_create(&t2, NULL, my_thread, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("%"PRIu64"\n", value);
  pthread_mutex_destroy(&m);

  return 0;
}

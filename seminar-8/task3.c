#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>

void *create_shared_memory(size_t size)
{
   return mmap(NULL,
               size,
               PROT_READ | PROT_WRITE,
               MAP_SHARED | MAP_ANONYMOUS,
               -1, 0);
}

// 0 - отрицательный индекс, 1 - вывести массив
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

   sem_t *parent_sem, *child_sem, *exit_sem;

   parent_sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
   child_sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
   exit_sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

   sem_init(parent_sem, 1, 0);
   sem_init(child_sem, 1, 0);
   sem_init(exit_sem, 1, 0);


   pid_t pid = fork();
   if (pid == 0)
   {
      int index = 0, new_value = 0;
      while (index >= 0)
      {
         printf("Enter array index and new value: ");
         scanf("%d %d", &index, &new_value);
         if (index >= 0 && index < 10)
         {
            arr[index] = new_value;
         }

         sem_post(parent_sem);
         sem_wait(child_sem);
      }
      sem_post(parent_sem);
      sem_post (exit_sem);
      return 0;
   }
   else
   {
      while (sem_wait(parent_sem) == 0 && sem_trywait(exit_sem) != 0)
      {
         for (int i = 0; i < 10; i++)
         {
            printf("Shared memory value at index %d: %d\n", i, arr[i]);
         }
         sem_post(child_sem);
      }

      waitpid(pid, NULL, 0);

      sem_destroy(parent_sem);
      sem_destroy(child_sem);
      sem_destroy(exit_sem);

      return 0;
   }
}

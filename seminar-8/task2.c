#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

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

   int pipes[2][2];
   pipe(pipes[0]);
   pipe(pipes[1]);

   pid_t pid = fork();
   if (pid == 0)
   {
      int index = 0, new_value = 0;
      int to_parent_pipe = pipes[1][1];
      int from_parent_pipe = pipes[0][0];

      close(pipes[1][0]);
      close(pipes[0][1]);

      int c = 1;
      while (index >= 0)
      {
         printf("Enter array index and new value: ");
         scanf("%d %d", &index, &new_value);
         if (index >= 0 && index < 10)
         {
            arr[index] = new_value;
         }

         write(to_parent_pipe, &c, 1);

         while (read(from_parent_pipe, &c, 1) == 0)
            ;
      }
      c = 0;
      write(to_parent_pipe, &c, 1);

      close(to_parent_pipe);
      close(from_parent_pipe);
      return 0;
   }
   else
   {
      int from_child_pipe = pipes[1][0];
      int to_child_pipe = pipes[0][1];

      close(pipes[1][1]);
      close(pipes[0][0]);

      int c;
      while (read(from_child_pipe, &c, 1) == 0)
         ;
      while (c)
      {
         for (int i = 0; i < 10; i++)
         {
            printf("Shared memory value at index %d: %d\n", i, arr[i]);
         }
         write(to_child_pipe, &c, 1);
         while (read(from_child_pipe, &c, 1) == 0)
            ;
      }

      waitpid(pid, NULL, 0);

      close(from_child_pipe);
      close(to_child_pipe);
      return 0;
   }
}

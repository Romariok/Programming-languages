/* fork-example.c */

#include <unistd.h>
#include <stdio.h>

int main() {
  // pid_t это, как и int, численный тип для идентификаторов процессов
  pid_t pid = fork();
  // в зависимости от возвращаемого значения, которое попадёт в pid, 
  // мы поймём, находимся ли мы в родительском процессе или в дочернем.
  if (pid == 0) {
      printf("I am a child, pid was %d\n", pid);
      printf("Child's pid is %d\n", getpid());
  }
  else {
      printf("I am a parent, pid was %d\n", pid);
      printf("Parent's pid is %d\n", getpid());
  }
}

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  pid_t pid;

  pid= getppid();

  printf("Parent's PID is: %d", pid);


  exit (0);
}

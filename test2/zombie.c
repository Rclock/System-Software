#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
  pid_t pid;
pid = fork();

if (pid > 0)
  {
    while (1)
      sleep(1);
  }
 else
   exit(0);


}

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main()
{
  pid_t pid;
  pid = fork();

  if (pid > 0)
    {
      int i;
      for (i=0; i<10; i++)
	printf("I am parent");

      //send signal to try to kill child SIGUSR1 signal to child
      
      
      //run 10 times more

    }
  if (pid == 0)
    {
      while (pid==0)
	printf("I am the child");


    }
  exit (0);

  


}

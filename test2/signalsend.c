#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>//this one works
int global = 0;
void handler(int sig)
{
  if (sig == SIGUSR1)
    {
      global = 2;
    }
   
}
int main()
{
  pid_t pid;
  pid=fork();
  
  if (pid == 0)
    {
      signal(SIGUSR1, handler);
       while (1)
	{  
	  printf("Child is running forever right now\n");
	  sleep(1); 
	  if (global == 2)
	    {
	      printf("Terminated by parents.");
	      exit(0);
	    }
	 
	}
        
    }
  else
    {
      int j, status;
      for (j=0; j < 10; j++)
	{
	  printf("I am the parent before signal\n");
	  sleep(1);
	}
      
        kill(pid, SIGUSR1);
	
      for (j=0; j < 10; j++)
	{
	printf("Parent running after kill system call\n");
      sleep(1);
	}
    }



 
 
}

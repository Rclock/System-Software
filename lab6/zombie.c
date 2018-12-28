#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
  pid_t pid;
  
  pid = fork();
  if (pid>0)
    {
      sleep(10);
	
    }
  else
    {
      exit(0);
 
    }
    

}

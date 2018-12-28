#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int agrc, char *argv[])
{
  pid_t pid;//to hold parent pid
  char *message;//to hold message
  int n;//for loop
  int sleeptime;//time for parent to sleep
    printf("fork program starting\n");
    pid = fork();//creates child process and returns parent pid in this case
    switch(pid)//takes care of determining if its a child or parent, do cases accordingly
    {
    case -1://fork error
        perror("fork failed");
        exit(1);
    case 0://child case (if fork() is ran from the child process it returns 0)
      message = "This is the child";//sets message
      n = *argv[1]-'0';//uses command line arguments
      sleeptime= *argv[3]-'0';//uses command line arguments
        break;
    default://parent case, usually a large number xxxxx 
      message = "This is the parent";
      n = *argv[2]-'0';//command line arguments for sleept times and iterations
       	sleeptime= *argv[4]-'0';
        break;
    }

    for(; n > 0; n--)//iterates over Nc or Np
    {
      puts(message);//outputs message and then sleeps 
        sleep(sleeptime);
    }
  
    
    exit(0);
}

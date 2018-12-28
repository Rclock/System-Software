#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int agrc, char *argv[])
{
    pid_t pid;
    char *message, *message2;
    int n;
    int sleeptime;
    int exit_code;
    printf("fork with exec program starting\n");
    
    //creates a child process
    pid = vfork();
    
    //char *args represents arguments to run child process off of
    char *args[]={"/home/ryan/cosc350/lab6/child", "This is the child, PID: ", argv[1], argv[3], NULL};

    
    switch(pid)
    {
    case -1:
        perror("fork failed");
        exit(1);
    case 0://in case of child process
      //executes child program using exec family of system calls
      execv(args[0], args);//executes child program using args array 
        break;
    default://for the parent, change correct arguments and variables. 
      message = "This is the parent, PID:";
	n = *argv[2]-'0';
       	sleeptime= *argv[4]-'0';
	exit_code=0;
        break;
    }
    //print parent process and it's ID
    for(; n > 0; n--)
    {
      printf("%s %d\n", message, getpid());//gets current process id
        sleep(sleeptime);
    }
       


  /*  This section of the program waits for the child process to finish.  */

    if(pid)
      {
        int stat_val;
        pid_t child_pid;

        child_pid = wait(&stat_val);

        printf("Child has finished: PID = %d\n", child_pid);
        if(WIFEXITED(stat_val))
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        else
            printf("Child terminated abnormally\n");
    }
   

     exit (exit_code);
 
}

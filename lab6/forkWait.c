#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int agrc, char *argv[])
{
  pid_t pid;//holds parent id/child id
    char *message;
    int n;
    int sleeptime;
    int exit_code;
    printf("fork program starting\n");
    pid = fork();//creates child process and return parent id in the first return
    switch(pid)
    {
    case -1://fork error
        perror("fork failed");
        exit(1);
    case 0://child case. fork() returns 0 if it is being run by the child process
        message = "This is the child";
	n = *argv[1]-'0';//uses command line arguments
	sleeptime= *argv[3]-'0';
	exit_code=37;
        break;
    default://parent case. fork() returns a larger number xxxxx for parent's pid 
        message = "This is the parent";
	n = *argv[2]-'0';//uses command line arguments
       	sleeptime= *argv[4]-'0';
	exit_code=0;
        break;
    }

    for(; n > 0; n--)//outputs message and sleeps depending on CL arguments
    {
	puts(message);
        sleep(sleeptime);
    }



  /*  This section of the program waits for the child process to finish.  */

    if(pid)
    {
        int stat_val;
        pid_t child_pid;

        child_pid = wait(&stat_val);

        printf("Child has finished: PID = %d\n", child_pid);
        if (WIFEXITED(stat_val))
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        else
            printf("Child terminated abnormally\n");
    }
   

     exit (exit_code);
 
}

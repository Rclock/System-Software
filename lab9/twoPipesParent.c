#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>
int main()
{
    int data_processed;
    int file_pipes[2];//parent to child pipe
    int file_pipes2[2];//child to parent pipe
    const char parentmessage[] = "Hi there, Kiddo";
    char buffer[BUFSIZ + 1];
    pid_t fork_result;

    int status;

    if (pipe(file_pipes) == 0)//open first pipe
        {
	  pipe(file_pipes2);//open second pipe
	  fork_result = fork();//creates child
	  if (fork_result == (pid_t)-1)//error checking
	{
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

	  if (fork_result == 0)//child case
	{
	  char  pipefd1[100], pipefd2[100];//use 2 arrays to pass the pipes to the child as args
	  
	  close(file_pipes[1]);//child reads from pipe 1
	  close(file_pipes2[0]);//child writes to pipe 2
	  sprintf(pipefd1, "%d", file_pipes[0]);//puts the pipe fd's into the char arrays
	     sprintf(pipefd2, "%d", file_pipes2[1]);

	     //execs twopipeschild with the pipe fd's as arguments
	     if(execl("twopipeschild", "twopipeschild", pipefd1, pipefd2, NULL) == -1)
	       printf("Exec Error");

	    
	  
            exit(EXIT_FAILURE);
        }
        else
	{
	  close(file_pipes[0]);//parent writes to pipe 1
	  close(file_pipes2[1]);//parent reads from pipe 2

	  //writes parentmessage to the child over first pipre
            data_processed = write(file_pipes[1], parentmessage, strlen(parentmessage));

	    //displays the wrote message
            printf("\nParent %d - wrote %d bytes over pipe 1\n", getpid(), data_processed);
	   

	    int stuffread;
	     wait(&status);//wait for child to finish so we're sure it wrote to the pipe
	     stuffread = read(file_pipes2[0], buffer, BUFSIZ);//reads from 2nd pipe

	     //displays child's message
	    printf("\nParent %d - read %d bytes over pipe 2:  %s\n", getpid(), stuffread, buffer);
  
	   
        }
    }
    exit(EXIT_SUCCESS);
}

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>
int main()
{
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "123";
    char buffer[BUFSIZ + 1];
    pid_t fork_result;

    int status;

    memset(buffer, '\0', sizeof(buffer));

    if (pipe(file_pipes) == 0)//if the pipe opened, go ahead and make a child
        {
	  
        fork_result = fork();
	
        if (fork_result == (pid_t)-1)//error case
	{
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        if (fork_result == 0)//child case
	{
       
	  sprintf(buffer, "%d", file_pipes[0]);//puts read end of pipe into argument array to use
	  (void)execl("pipe4", "pipe4", buffer, NULL);
	    close(file_pipes[0]);
            exit(EXIT_FAILURE);
        }
        else
	{
	  close(file_pipes[0]);
            data_processed = write(file_pipes[1], some_data,
                                   strlen(some_data));//write over pipe1 to child
	    
            printf("%d - wrote %d bytes\n", getpid(), data_processed);//
	    close(file_pipes[1]);
  
	    wait(&status);//added
        }
    }
    exit(EXIT_SUCCESS);
}

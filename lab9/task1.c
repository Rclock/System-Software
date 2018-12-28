#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int READ_END = 0;
int WRITE_END = 1;
int main()
{
    int data_processed;
    int file_pipes[2];//pipe to use
    const char some_data[] = "123";
    int bufsize;
    char *buffer;
    buffer = (char*) malloc(sizeof(char)*(3));
    strcpy(buffer, some_data);//puts some_data into buffer
    memset(buffer, '\0', sizeof(buffer));

    if (pipe(file_pipes) == 0) {//in child
      data_processed = write(file_pipes[WRITE_END], some_data, strlen(some_data));//writes to pipe
      printf("Wrote %d bytes\n", data_processed);
      data_processed = read(file_pipes[READ_END], buffer, sizeof(buffer));//reads from pipe
        printf("Read %d bytes: %s\n", data_processed, buffer);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}

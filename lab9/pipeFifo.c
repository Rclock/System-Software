#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
int main()
{
    int data_processed;
    int fd;
    const char some_data[] = "123";
    char buffer[3];
    
    strcpy(buffer, some_data);
   
    fd = open("/tmp/task4_fifo", O_RDWR);//opens the fifo created on the CL at /tmp/task4_fifo 
    
    data_processed = write(fd, buffer, strlen(buffer));//writes some_data to the fifo
        printf("Wrote %d bytes\n", data_processed);
        data_processed = read(fd, buffer, strlen(buffer));//reads into the buffer from the fifo
        printf("Read %d bytes: %s\n", data_processed, buffer);
        exit(EXIT_SUCCESS);
}

/*client1.c which send two integer through FIFO to server1.*/
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define HALF_DUPLEX "halfduplex"
#define BFFERSIZE 20
int main(int argc, char *argv[])
{
 int fd, n;
 char buffer[BFFERSIZE];
 /* Open the FIFO for writing */
 fd = open(HALF_DUPLEX, O_WRONLY);

 printf("Enter two integers\n Press Ctrl+D to exit\n");
 
 while(read(0, buffer, BFFERSIZE)!=-1)
 {
   write(fd,buffer,strlen(buffer)); //pass information from to child through FIFO
 }
}

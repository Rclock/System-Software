/*server1.c which receive two integer through FIFO and calculate it’s sum.*/
#include <stdlib.h>
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
  
 int fd, retval, count, numread;
 char buffer[20];
 
 /* Create the named - pipe */
 retval = mkfifo(HALF_DUPLEX, 0666);


 /* Open the FIFO for reading */
 fd = open(HALF_DUPLEX, O_RDONLY);
 int int1, int2, n, sum;

 while((n=read(fd, buffer, BFFERSIZE))>0)
 {
buffer[n]='\0';
 
 if (sscanf(buffer, "%d %d", &int1, &int2)== 2)
 {
 sprintf(buffer, "The sum is %d\n", int1+int2);
 write(1, buffer, strlen(buffer));
 }
 
 else
 write(1, "invalid arguments\nEnter two integers\n", 37);
 
 }
}

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
void err_system(char *string);
int main()
{

  int filedescriptorIn, filedescriptorOut;
  char byte;
  umask(0);
  if(( filedescriptorIn = open("foo.in", O_RDONLY)) == -1)
    err_system("open");
  
  if (( filedescriptorOut = open("clone1.out", O_RDWR|O_CREAT, 0666)) == -1)
    err_system("open");
			    
      while (read(filedescriptorIn, &byte, 1) > 0)
	if (write(filedescriptorOut, &byte, 1) != 1)
	  err_system("Write");

      exit (0);
}
void err_system(char *string)
{

  printf("%s Error!", string);
  exit (1);
}

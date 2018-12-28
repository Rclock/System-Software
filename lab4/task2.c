#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
void syserror(char *string);
int main(int argc, char *argv[])//take 2 arguments, filein and fileout
{
  int filein, fileout;
  umask(0);//clears permissions 
  
  if ((filein=open(argv[1], O_RDWR)) == -1)//exits if the input file is not available
    {
    printf("Opening error for input file. Input file not available. The program will exit now. ");
    exit (1);
    }
  
  if ((fileout=open(argv[2], O_CREAT|O_RDWR, 0777)) == -1)//opens file for outpu
    syserror("Open");
  
  char buffer[64];
  int nread;
  while (nread = read(filein, buffer, 64))//uses a buffer of size 64, you could do any size. It does not have to be 64, it could be 1. 
    {
      write(fileout, buffer, nread);//writes number of bytes read to fileout
    }
  exit (0);
}
void syserror(char *string)
{
  printf("%s Error!", string);
  exit (1);
}

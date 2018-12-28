#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
void syserror(char *str)
{
  printf("%s", str);
  exit (1);

}
#define BUFF_SIZE 32
int main()
{


  
  char buffer[BUFF_SIZE];
  int filedIN, filedOUT;
  int nbyte;

  umask(0);  
  if (( filedIN = open("foo.in", O_CREAT|O_RDWR)) == -1)//open for reading
    syserror("open");
  
  if (( filedOUT = open("clone2.out", O_CREAT|O_RDWR, 0770)) == -1)//open for writing
    syserror("open");

  
  while ((nbyte = read(filedIN, buffer, BUFF_SIZE)) > 0)//read with 32 size buffer
    {
      if (write(filedOUT, buffer, nbyte) != nbyte)/*writes same # of bytes read to outut file*/
      syserror("Writing Error!");

    }

  exit (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
  char a;
  int fd1;
  fd1=open(argv[1], O_RDWR);
  int size;
  size = lseek(fd1, 0, SEEK_END);
  lseek(fd1, 0, SEEK_SET);
  int i;
  for (i=0; i< size; i++)
    {
      read(fd1, &a, 1);
  if (a >= '0' && a <= '9')
    {
    write(1, &a, 1);
    }
  else
    {
    printf("Not an integer");
    }
    }

  exit (0);
}

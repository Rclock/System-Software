#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
void sys_Error(char *string)
{
  printf(" %s Error!", string);
  exit (1);
}
int main(int argc, char *argv[])
{
  umask(0);
  if (argc != 3)//3 includes program name. IF not a program name and 2 files, quit. 
    {
     printf("Error, enter 2 arguments only. ");
  exit (1);
    }

  int in, out;
  
  while(  (in = open(argv[1], O_RDWR)) < 0)//open first file for input
    {
    printf("Error");
    exit (1);}
 
  while ( ( out = open(argv[2], O_RDWR|O_CREAT, 0666)) < 0)//open 2nd file for output
    {
      printf("Error");
      exit (1);

    }
    
    
  
  dup2(out, 1);//this makes it so printf will now print to the out file descriptoer
  char a;
  while (read(in, &a, 1) == 1)//reads byte by byte and prints as an int (ASCII)
    {      
      
      printf("%d ", a);
    }
  
  exit (0);

}

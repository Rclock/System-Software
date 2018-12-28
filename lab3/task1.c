
/* makes a buffer size of 32 and uses standard input to fill buffer and then write it to standard input */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void err_system(char *string);
int main()
{
  char buffer[32];//use size 32, can use any size because i only write nread 
  int nread;
 
  while ((nread = read (0, buffer, 32))!= -1)//writes number of bytes read to 1
  {
    if ((write(1, buffer, nread)) == -1)
      err_system("write");



  }
exit (0);

 
}
void err_system(char *string)
{

  printf("%s Error!", string);
  exit (1);
}

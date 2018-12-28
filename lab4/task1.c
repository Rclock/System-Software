#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
void err_system(char *string);
int convIntToStr(char *str, int x);
int main(int argc, char *argv[])
{
  int filein;
  if ((filein = open(argv[1], O_RDWR)) < 0)
    err_system("Open");
  
   int size = lseek(filein, -1, SEEK_END);//just doing this to get the size of file
 
  int count;
  int count2 = 0;
  char buffer[size];
  char array[size];
  char a;
   lseek(filein, 0, SEEK_SET);//reset the seek position
    for (count = 0; count < size; count++)//accumulates into char array
	 {
            char a;
	    if (( read(filein, &a, 1)) == -1)
	      err_system("read");
	    
	   buffer[count] = a; 
      int b = buffer[count];
      
    if (isdigit(b) != 0)
  	{
  	  array[count2] = b;
  	  printf("Added %c to array\n", b);
	  count2++;
  	}
    
   
     }
  int k;
  int integers[count2];
  int sum;
  for (k = 0; k < count2; k++)//converts string to integer values (ASCII)
    {
      integers[k] = array[k]-'0';
      sum = integers[k] + sum*10;//adds up each digit 
    }
  sum = sum + 10;//adds 10 to integer

  printf("Sum: %d", sum);
   char buffer2[count2];

   int length =  convIntToStr(buffer2, sum);//converts integer back to string

   printf("Here is the string after all operations: \n");
   
   
   write(1, buffer2, length);
   printf("\n");
   close(filein);
  exit (0);
}

void err_system(char *string)
{
  printf("%s Error!", string);
  exit (1);

}
int convIntToStr(char *str, int x)
{
  
    sprintf(str, "%d", x);
  return (strlen(str));
}

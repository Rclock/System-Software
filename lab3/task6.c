#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void error();
int string_integer(char *string);
int main(int argc, char *argv[])
{
  if (argc < 2)
    error();


  int i;
  
  int j;
  int sum = 0;
   
  for (i=1; i < argc; i++)//runs for each argument of the command line
    { 
      sum = sum + string_integer(argv[i]);//adds up each integer on CL
    }

  printf("Sum of integers is: %d\n", sum);//prints sum


  exit (0);
}

void error()
{
  printf("You did not enter at least one integer on the commmand line. goodbye. ");
  exit (1);

}
int string_integer(char *string)
{
  int i = 0;
  int sum = 0;
    for (i = 0; string[i] != '\0'; i++)//loops until we are not at end of string
       {
      
	 sum = (sum*10) + (string[i] - '0');//adds up each integer, *10 for more than one digit integers

  
       }
  return sum;
}


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 256

int main(int argc, char *argv[])
{
  char buffer[BUFSIZE];//used to store output of cmd
  char cmd[32];//to store the command given
  FILE *file;//file to associate with popen
  
  int i;
  for (i=1; i < argc; i++)//use a loop so we can take care of many arguments
    {
      if (i==1)//start the cmd string with first argument before using strcat
	strcpy(cmd, argv[i]);
      else
       strcat(cmd, argv[i]);
      
      strcat(cmd, " "); //space between each argument
    }
    
   file = popen(cmd, "r");//executes cmd in the child and connects file to the output of the cmd string 
   
   for ( ; ; )//for loops runs forever unless break is given
   {
         if (fgets(buffer, BUFSIZ, file) == NULL)//stores in the buffer the contents in the file stream from execution, keeps going using a 256 byte buffer
      break;//once we read everything we stop reading

         if (fputs(buffer, stdout) == EOF)//prints to stdout what is in the buffer each time
     printf("\nError\n ");
      
   }
 
  exit(0);
}


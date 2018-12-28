// The 'consumer' program, pipe4.c, that reads the data is much simpler.
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int data_processed;
  char buffer[BUFSIZ + 1];
  int file_descriptor, file_descriptor2;
  const char childmessage[] = "Hi Mom";
  
  sscanf(argv[1], "%d", &file_descriptor);//puts what is in the char array for the pipefd into an integer to use

  data_processed = read(file_descriptor, buffer, BUFSIZ);//read from pipe 1 (parentmessage)
  printf("\nChild %d - read %d bytes over pipe 1: %s\n", getpid(), data_processed, buffer);//displays parentmessage read from pipe1
  
  sscanf(argv[2], "%d", &file_descriptor2);//puts argv2 (pipefd2 from parent) into an integer to use
  int stuffwrote;
  stuffwrote = write(file_descriptor2, childmessage, strlen(childmessage));//writes childmessage over pipe 2 to parent
  printf("\nChild %d - Wrote %d bytes over pipe 2\n", getpid(), stuffwrote);//dsplays wrote notification 
  exit(EXIT_SUCCESS);
}

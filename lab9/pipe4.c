// The 'consumer' program, pipe4.c, that reads the data is much simpler.
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int data_processed;
  char buffer[BUFSIZ + 1];
  int file_descriptor;

  memset(buffer, '\0', sizeof(buffer));
  sscanf(argv[1], "%d", &file_descriptor);//puts argv1 (read end of pipe) into a fd integer
  data_processed = read(file_descriptor, buffer, BUFSIZ);//read over pipe 1 from parent

  printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
  exit(EXIT_SUCCESS);
}

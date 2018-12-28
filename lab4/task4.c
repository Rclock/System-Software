#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char cwd[PATH_MAX];
  
  getcwd(cwd, sizeof(cwd));


  
  //tack on argv[1] after the cwd. Then use this as the current path to be moved from. 
  strcat(cwd, "/");
  strcat(cwd, argv[1]);
  printf("%s", cwd);
  
  
  link(cwd, argv[2]);
  //unlink(argv[1]);

  exit (0);
}

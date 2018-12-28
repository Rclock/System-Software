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
  struct stat buf;
  char cwd[PATH_MAX];
  
  getcwd(cwd, sizeof(cwd));
  
  //tack on argv[1] after the cwd. Then use this as the current path to be moved from. 
  strcat(cwd, "/");
  strcat(cwd, argv[1]);
  printf("CWD with file name is: %s\n", cwd);
  
 
  printf("Path of place to move to is: %s\n", argv[2]);


  stat(argv[2], &buf);
  
  if (S_ISDIR(buf.st_mode))
    {
      printf("\nArgument 2 is a directory");
      strcat(argv[2], "/");
      strcat(argv[2], argv[1]);
      printf("Place to move is now: %s", argv[2]);
      link(cwd, argv[2]);
       
    }
    else
    {
      
	printf("\nArgument 2 was not a directory.");
	link(argv[1], argv[2]);
    }
    
 
  
  unlink(cwd);

  exit (0);
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char *mygetenv( char *name);
extern char **environ;//a built in pointer to all of the environment variables
int main(int agrc, char *argv[])
{
  
  char *env1 = mygetenv(argv[1]);//works the same as getenv()
  printf("Here it is: %s\n", env1);//displays value of environment variable
  exit (0);
}
char *mygetenv(char *name)
{
  char **env = environ;//makes an env double pointer with same pointers as environ

  char *test = NULL;//test pointer to compare pointer values
  while (*env)//iterates over double pointer and increments each time
    {
      test=strstr(*env, name);//tests if the current *env starts with char *name
      if (test == *env)//if it does start with the whole input string, the whole word is most likely the variable. (checked all environ variables, it will always work)
	{
	return *env;
	}
        env++;//if it hasn't been found, move on to the next pointer. 
     }

}


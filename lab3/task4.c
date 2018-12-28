
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
void err_system(char *string);
int main()
{

  int nbyte, nbyte1, foodes, foo1des, foo12des;
  char a, b;
  
  foodes= open("foo.in", O_RDONLY);//opens first file for input
  
  if (foodes < 0)//checks for error in opening
    err_system("open");
  
    foo1des= open("foo1.in", O_RDONLY);//opens second file for input
		
    if (foo1des < 0)//checks for error in opening
  err_system("open");
  
  umask(0);//clears permission setting constraints
  
  foo12des = open("foo12.out", O_WRONLY|O_CREAT, 0760);//opens output file for output

  if (foo12des < 0)//makes sure there is no open error
  err_system("open");
  
 
     while ((nbyte = read(foodes, &a, 1)) == 1)//reads first file byte by byte/writes
    {
      
      write(foo12des, &a, nbyte);
      
    }

  lseek(foo12des, -1, SEEK_END);//sets new read position right after we just stopped
  while ((nbyte1 = read(foo1des, &b, 1)) == 1)//reads/writes second file to output file
    {      
      write(foo12des, &b, nbyte1);
    }

  return 0;
}
void err_system(char *string)
{

  printf("%s Error!", string);
  exit (1);
}

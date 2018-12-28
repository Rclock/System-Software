#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
int isnumeric(char a);
int main(int argc, char *argv[])
{
  umask(0);
  int fd1, fd2, fd3;
  
  
  if ((fd1=open(argv[1], O_RDWR)) == -1)//open file for input for both files
      printf("open error");
     
  int size = lseek(fd1, 0, SEEK_END);
  
  pid_t pid;
  if ((pid = fork()) == -1) //fork a child process
    printf("Fork error");
  
  int nreadp, nreadc = 0;//used for parent and child read number
  
  if (pid != 0)//for the parent process
    { 
      char a;
      
      if ((fd2 = open("parent.txt", O_CREAT|O_RDWR, 0777)) == -1)//output file
	printf("Open error");

      int j;
      for (j = 0; j < size; j++)//read byte by byte
	{
	  lseek(fd1, j, SEEK_SET);
	 nreadp= read(fd1, &a, 1);
	  if (isnumeric(a))//it is numeric
	    {
	      
	      if ((write(fd2, &a, nreadp)) < 0)//write byte by byte
		printf("Write error");
	      
	    }
	}
       
    }
  if (pid == 0)
    {
      if ( (lseek(fd1, 0, SEEK_SET)) == -1)//synchronize
      printf("Seek Error");

      
      char b;
      if ((fd3 = open("child.txt", O_CREAT|O_RDWR, 0777)) == -1)//open output file
	printf("Open Error");
      int i;
      for (i = 0; i < size; i++)//read byte by byte
	{
	 nreadc= read(fd1, &b, 1);
	  lseek(fd1, i, SEEK_SET);
	  
	 if (!isnumeric(b))//it is not a numeric
	    {
	      if ((write(fd3, &b, nreadc)) < 0)//write byte
		printf("Write error");
	    }
	}
    }

  exit (0); 
}


int isnumeric(char a)//function to check for numeric or not
{
  if (a >= '0' && a <='9')
    {
      return 1;
    }
  else
    return 0;
}

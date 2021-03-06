#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int LOCK;
void handler(int sig)
{
  if (sig == SIGUSR1)
    LOCK = 1;

}
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
      
      lseek(fd1, 0, SEEK_SET);
      char a;
      
      if ((fd2 = open("parent.txt", O_CREAT|O_RDWR, 0777)) == -1)//output file
	printf("Open error");
      signal(SIGUSR1, handler);//turn LOCK to 1
      raise(SIGUSR1);//sends SIGUSR1 to itself
      
      if (LOCK!=0)
	{
     
      int j;
      for (j = 0; j < size; j++)//read byte by byte
	{
	  nreadp= read(fd1, &a, 1);
	  if (isnumeric(a))//it is numeric
	    {
	      
	      if ((write(fd2, &a, nreadp)) < 0)//write byte by byte
		printf("Write error");
	      
	    }
	}
	}
      LOCK = 0;
    }
  if (pid == 0)
    {
      if (LOCK!=0)
	{
      lseek(fd1, 0, SEEK_SET);
      char b;
      if ((fd3 = open("child.txt", O_CREAT|O_RDWR, 0777)) == -1)//open output file
	printf("Open Error");
     signal(SIGUSR1, handler);//LOCK variable = 1 before critical section
      raise(SIGUSR1);//send SIGUSR1 to itself
      
      int i;
      for (i = 0; i < size; i++)//read byte by byte
	{
	 nreadc= read(fd1, &b, 1); 
	 if (!isnumeric(b))//it is not a numeric
	    {
	      if ((write(fd3, &b, nreadc)) < 0)//write byte
		printf("Write error");
	    }
	}LOCK = 0;
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

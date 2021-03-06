#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
  
  int fd1,size;
  umask(0);
  pid_t pid;
  pid=fork();
  char *message;
  fd1= open("foo", O_CREAT|O_RDWR, 0777);//open file for child to write to  
  size=lseek(fd1, 0, SEEK_END);//get size of file
  if (pid == 0)//child process
    {
      message = "Hi Mom";//child's message
      
      lseek(fd1, 0, SEEK_SET);//reset seek position
      write (fd1, message, 6);//write message to the file 
    }
 
  if (pid > 0)//parent process
    {
      int status;
      wait(&status);

      size = lseek(fd1, 0, SEEK_END);//get size of file
      lseek(fd1, 0, SEEK_SET);//reset seek position
      char buffer[size];
      read(fd1, &buffer, size);
      printf("My son said %s", buffer);
    }
  printf("\n");  
   
  exit (0);
}

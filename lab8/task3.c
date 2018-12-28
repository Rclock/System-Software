#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 256
void err_sys(char *);
int main()
{
 int n, fd[2], size, int1, int2;
 pid_t pid;
 char buffer[MAXLINE], buffer2[MAXLINE];
 
 pipe(fd);//creates a pipe
 
 pid = fork();//fork child 
 
 if (pid > 0) /* parent use the pipe to send message to child*/
 {
   close(fd[0]); //closes read end of pipe
   printf("submit two integers\n");
 
     while ( (size = read(1, buffer, MAXLINE)) > 0)
     {
       write(fd[1], buffer, size); /*write to a pipe */
       printf("submit two integers\n");
     }
 }
 
 else /* child use pipe to receive message from the parent */
 {
 close(fd[1]); /* fd[1] need to be close since fd[0] is used for receiving data */

     while ((n = read(fd[0], buffer2, MAXLINE))>0) /*read from the pipe */
     {
 /* chose first two string as two integer */

   if (sscanf(buffer2, "%d %d", &int1, &int2) == 2)
     {
   
      sprintf(buffer2, "%d\n", int1 + int2);
      n = strlen(buffer2);
   
   if (write(1, buffer2, n) != n)
     err_sys("write error");
    memset(buffer2, 0, MAXLINE);
     }
   
   
   else /* if first two string is not integer */
     {
  
if (write(1, "invalid args\n", 13) != 13)
 err_sys("write error");
 
     }
   
 }
 
 }
 exit(0);
}
void err_sys(char *str)
{
 printf ("%s \n",str);
 exit (1);
}

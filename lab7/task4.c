#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
static int global;
void response1(int sig)
{
  if (sig==SIGUSR1)
    global=1;
}
void response2(int sig)
{
  if (sig==SIGUSR2)
    global=2;
}

int main()
{
  int i;
  pid_t childpid1, childpid2;
   
  childpid1=fork();//create first child
      
  if (childpid1 == 0)
    {
      
      kill(getppid(), SIGUSR1);//in first child, send SIGUSR1 to parent
  
    }
  else//in parent
    {
      signal(SIGUSR1, response1);//catch SIGUSR1 from first child
      pause();
if (global==1)
  printf("Hi Honey! Anything wrong?\n");
childpid2=fork();//create second child
      if (childpid2 == 0)
{
  kill(getppid(), SIGUSR2);//send SIGUSR2 to parent
}
      else//still in parent from above
{
  signal(SIGUSR2, response2);//catch SIGUSR2 from second child
  pause();       
if (global == 2)
   printf("Did you make trouble again?\n");
 }                      
                             
    }  

  exit (0);

}

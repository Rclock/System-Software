#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void handler(int sig)
{



}
int main()
{
  int i;
  sigset_t oldset;
  sigset_t newset;
  
  sigemptyset(&newset);//makes new an empty mask
  sigemptyset(&oldset);//makes old an empty mask
  sigaddset(&oldset, SIGINT);//adds SIGINT to old
  sigaddset(&newset, SIGINT);//adds SIGINT to new
  sigaddset(&newset, SIGQUIT);//adds SIGQUIT to new

  struct sigaction quit;
  quit.sa_handler = handler;//quit in the first loop will do nothing, it's also blocked
  struct sigaction quit2;//used to reset back to quit being used to quit

  sigprocmask(SIG_SETMASK, &newset, NULL);//blocks SIGINT and SIGQUIT
  sigaction(SIGQUIT, &quit, &quit2);//uses quit and it's handler function to do nothing on SIGQUIT (so its not used in second loop)
  for (i=0; i < 5; i++)
    {
      printf("%d\n", i+1);
      sleep(1);
    }
  
  

   sigprocmask(SIG_SETMASK, &oldset, NULL);//update to just SIGINT
   sigaction(SIGQUIT, &quit2, NULL);//resets action of SIGQUIT 
   
  int j;
  for (j=0; j<5; j++)
    {
      printf("%d\n", j+1);
      sleep(1);
    }

  exit (0);
}

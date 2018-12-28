#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig)
{
    printf("OUCH! - I got signal %d\n", sig);
}

int main()
{
    struct sigaction act;

    act.sa_handler = ouch;//assigns ouch as the handler function
    sigemptyset(&act.sa_mask);//makes the mask empty
    act.sa_flags = SA_RESETHAND;

    sigaction(SIGINT, &act, 0);//makes ouch execute when SIGINT is issued (once)

  while(1) {
    printf("Hello World!\n");
    sleep(1);
  }
}

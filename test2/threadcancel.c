#include <pthread.h>
11;rgb:3030/0a0a/2424#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
void *Bye()
{
  printf("\nBye\n");
}
void *th1(void *arg)
{
  int id;
  id = (int)arg;
  int i = 0;
  while (i <15)
    {

      i++;
      
      if ( i == 10)
      pthread_cancel(id);
      
    }
  
  pthread_exit(NULL);
}
void *th2(void *Arg)
{
  pthread_cleanup_push(Bye, NULL);

  while (1)
    {
      printf("Running forever\n");
      pthread_testcancel();//sets up termination point
    }

  pthread_exit(NULL);

}

int main()
{
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, th1, (void *)thread1);
  pthread_create(&thread2, NULL, th2, NULL);

  pthread_join(thread2, NULL);
  pthread_join(thread1, NULL);

  pthread_exit(NULL);
  exit(0);  
}

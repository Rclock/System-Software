#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int convertinteger(char *string)//my own atoi function
{
  int i;
  int sum = 0;
  for (i=0; string[i] !='\0'; i++)
    {
      sum = (string[i]-'0') + sum*10; 
    }
  return sum;

}

void *factorialfunc(void *arg)//calculates factorial
{
  
  int count = (int)arg;
  int factorial=1;
  while (count > 0)//calculates factorial
    {
     factorial = factorial * count;
     count--;
    }
  printf("Factorial is: %d\n", factorial);
  pthread_exit(NULL);
  
}
void *addfunc(void *arg)//adds up the integers making up the argument
{
  int count = (int)arg;//casts count as the argument as an integer
  int sum = 0;
  while (count > 0)
    {
      sum = sum + count;
      count--;
    }
  printf("Sum is: %d\n", sum);
  pthread_exit(NULL);
  
  
}
int main(int argc, char *argv[])
{
  pthread_t thread1;
  pthread_t thread2;
  int k;
  k = convertinteger(argv[1]);
  
  printf("Here is k: %d\n", k);
  pthread_create(&thread1, NULL, factorialfunc, (void *)k);
  pthread_create(&thread2, NULL, addfunc, (void *)k);
  pthread_exit(NULL);
  exit(0);
}

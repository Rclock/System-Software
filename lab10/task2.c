#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#define COUNT 10
pthread_mutex_t countmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t conditionmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;
int produceitem();
void consumeitem(int item);
int array[COUNT];
int count = 0;
int global = 0;
void *producerfunc()
{  
  int item;
  while (1)
    {
      item = produceitem();
       pthread_mutex_lock(&conditionmutex);//lock condition mutex
              
       if (count == COUNT)
	 {
	   printf("Producer sleeping\n");
   	   pthread_cond_wait(&condition_cond, &conditionmutex);//"sleep"
	 }
       
       if (array[count] == 0)//otherwise there is already an element here
	 {
	   printf("Producer inserted %d at index %d\n", item, count);
	 array[count] = item;//"insert"
	 }
       
       pthread_mutex_lock(&countmutex);
       count++;
       pthread_mutex_unlock(&countmutex);
   
        if (count == 1)
	{
	  pthread_cond_signal(&condition_cond);//wake up consumer
	}
	pthread_mutex_unlock(&conditionmutex);//unlocks condition mutex
    }
}
void *consumerfunc()
{
  int item;

  while (1)
    {

      if (count == 0)
	{
	printf("Consumer is sleeping\n");
	pthread_cond_wait(&condition_cond, &conditionmutex);//sleeps
	}
        item = array[count];//realloc and calloc?
      pthread_mutex_lock(&countmutex);//lock count mutex to change the global count variable
        count--;
      pthread_mutex_unlock(&countmutex);//unlock count mutex 
      
      if (count == (COUNT-1))
	{
    	  pthread_cond_signal(&condition_cond);//wakes up the producer
	  
	}
      if (item != 0)//otherwise this spot was empty anyway
	{
	  printf("Consumer consumed %d at index %d\n", item, count);
	  consumeitem(item);
	}
      pthread_mutex_unlock(&conditionmutex);//unlock condition mutex                                 
           

    }
  pthread_exit(NULL);
}
int produceitem()
{
  int item;
  item = rand() % 10 + 1;
  return item; 
}
void consumeitem(int item)
{
  array[item] = 0;
}
int main()
{  
    pthread_t producer, consumer;
    pthread_create(&producer, NULL, &producerfunc, NULL);
    pthread_create(&consumer, NULL, &consumerfunc, NULL);
  
    pthread_join(producer, NULL);//waits for thread1 
    pthread_join(consumer, NULL);//waits for thread2

  pthread_exit(NULL);
  exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int *array;//global variables
int size = 0;//global variables
int count = 0;//global variables
void bubbleSort(int *arr,int length)//bubble sort to get max and min
{
   pthread_mutex_lock(&mutex1);

   int swap;
   int temp;
   do
   {
     swap = 0;
     int count1;
     for (count1 = 0; count1 < (length-1); count1++)
     {
      if (arr[count1] > arr[count1 + 1])
      {
        temp = arr[count1];
	arr[count1] = arr[count1 + 1];
	arr[count1 + 1] = temp;
        swap = 1;
      }
     }
    } while (swap);
    pthread_mutex_unlock(&mutex1);

}
void *input()//thread1
{
  int i;
  int b;
  pthread_mutex_lock(&mutex1);
  
  for (i=0; i < size; i++)
    {
     
          printf("Enter a value\n");
          scanf("%d", &b);
 
	  array[i] = b;
	  count++;
    }
  pthread_mutex_unlock(&mutex1);
  pthread_exit(NULL);

}
void *meanavg()//thread2
{
   pthread_mutex_lock(&mutex1);

  int j;
  int sum = 0;
  float avg = 0;

  for (j = 0; j < size; j++)//calculates sum
    {
      sum = array[j] + sum;
    }
  
  avg = (float)sum/(float)count;//
  printf("Here is the average: %.2f\n", avg);
  
  float median;
  if ((size % 2) == 0)
      median = array[size/2] + array[(size/2)-1];
      median = (median/2);

 
  if ((size % 2) != 0)
    {
          median = array[size/2];
    }
  
  printf("Here is the median: %.2f\n", median);
   pthread_mutex_unlock(&mutex1);

  pthread_exit(NULL);
}

void *maxmin()
{
  pthread_mutex_lock(&mutex1);
  
  float min = array[0];//min after array is sorted
  float max = array[size-1];//max after array is sorted
  
  printf("\nThe min is: %.2f\n", min);
  printf("The max is: %.2f\n", max);
  
  pthread_mutex_unlock(&mutex1);

  pthread_exit(NULL);
}
void *clear()
{
  printf("Thread 4 now clearing array\n");
  memset(array, 0, count);

  pthread_exit(NULL);
}

int main()
{
  
  pthread_t thread1, thread2, thread3, thread4;//threads
  printf("Enter the number of test scores you want to enter\n");
  scanf("%d", &size);
  if (size > 20)
    exit(0);
  array=(int*)malloc(sizeof(int)*size);//malloc 
  pthread_create(&thread1, NULL, input, NULL);//first thread runs
  pthread_join(thread1, NULL);//waits for first thread to finish job
  bubbleSort(array, count);//sort using bubble sort
  pthread_create(&thread2, NULL, meanavg, NULL);//run thread 2
  pthread_create(&thread3, NULL, maxmin, NULL);//run thread 3
  pthread_join(thread2, NULL);//wait for thread 2
  pthread_join(thread3, NULL);//wait for thread 3
  pthread_create(&thread4, NULL, clear, NULL);//thread 4 goes after 2 and 3
  pthread_exit(NULL);
  exit (0);
}

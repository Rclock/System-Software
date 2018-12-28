#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#define N 10
typedef int semaphore;
semaphore mutex = 1;
semaphore empty = N;
semaphore full = 0;
void *producer();
void *consumer();
int produceitem();
void consumeitem(int item);
void insertitem(int index, int item);
int removeitem(int index);
void up(int index);
void down(int index);
int semid;
union semun
{
int val; /* for SETVAL */
struct semid_ds *buf; /* for IPC_STAT and IPC_SET */
unsigned short *buffer; /* for GETALL and SETALL */
};

int buffer[N];
union semun arg;
int main(int argc, char *argv[])
{
  pthread_t producert, consumert;
  key_t key;
  umask(0);
  
  key = ftok("task3.c", 'B');//creates a key
  semid = semget(key, 3, 0666|IPC_CREAT);//creates a sem buffer 
  arg.val = 1;
  semctl(semid, 0, SETVAL, arg);//sets values of first sem, mutex, to 1
  arg.val = 10;
  semctl(semid, 1, SETVAL, arg);//sets value of 2nd sem, empty, to EMPTY(10)
  arg.val = 0;
  semctl(semid, 2, SETVAL, arg);//sets value of 3rd sem, full, to 0
  
  pthread_create(&producert, NULL, &producer, NULL);//runs the producer
  pthread_create(&consumert, NULL, &consumer, NULL);//runs the consumer
  
  pthread_join(producert, NULL);//waits for producer to finish
  pthread_join(consumert, NULL);//waits for consumer to finish
  
  semctl(semid, 0, IPC_RMID, arg);//deletes the semaphore array
  pthread_exit(NULL);
  exit (0);
}
int produceitem()
{
  int item = rand() % 10 + 1;
  return item;
}
void consumeitem(int index)
{
  if (buffer[index] != 0)
    {
    buffer[index] = 0;
    printf("\nConsumer took out item from index %d\n", index);
    }
}
void insertitem(int index, int  item)
{
  if (buffer[index] == 0)
    {
      buffer[index] = item;
      printf("\nProducer inserted %d into index %d\n", item, index);
    }
}
int removeitem(int index)
{
  int item;
  item = buffer[index];
  return item;
}
void *producer()
{
  int bound = 0;
  int item;
  
  while(1)
  {
      item = produceitem();
      down(1);//down(empty)
      down(0);//down(mutex)
      int index;
      index = semctl(semid, 2, GETVAL);//gets value of the countable full
      insertitem(index, item);
      up(0);//
      up(2);//
  }
  
  pthread_exit(NULL);
}
void *consumer()
{
  int item;
  int bound1;
  while(1)  
  {
    down(2);//down(full)
    down(0);//down(mutex)     
    int index1;
    index1 = semctl(semid, 1, GETVAL);//get the value of empty
    item = removeitem(index1);                                                             
    consumeitem(index1);
    up(0);//up(mutex)
    up(1);//up(empty)
     
  }
 
  pthread_exit(NULL);
}
void down(int index)
{
  struct sembuf sb = {index, -1, 0};
  if (semop(semid, &sb, 1) == -1)
    perror("Semop");
}
void up(int index)
{
  struct sembuf sb = {index, 1, 0};
  if (semop(semid, &sb, 1) == -1)
    perror("Semop");
}


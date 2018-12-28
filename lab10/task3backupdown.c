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
void down(semaphore *sem, int index);
void up(semaphore *sem, int index);
void consumeitem(int item);
int semid;
union semun
{
int val; /* for SETVAL */
struct semid_ds *buf; /* for IPC_STAT and IPC_SET */
unsigned short *buffer; /* for GETALL and SETALL */
};

int buffer[N];
union semun arg;
union semun arg1;
union semun arg2;

int main(int argc, char *argv[])
{
  pthread_t producert, consumert;
  key_t key;
  umask(0);
  
  key = ftok("task3.c", 'B');//creates a key
  semid = semget(key, 3, 0666|IPC_CREAT);//creates a sem buffer 
  arg.val = 1;
  semctl(semid, 0, SETVAL, arg );//sets values of first sem, full, to FULL
  arg1.val = 10;
  semctl(semid, 1, SETVAL, arg1);//sets value of 2nd sem, empty, to EMPTY(10)
  arg2.val = 0;
  semctl(semid, 2, SETVAL, arg2);//sets value of 3rd sem, mutex, to 1

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
void consumeitem(int item)
{
  buffer[item] = 0;
}
void *producer()
{
  int bound = 0;
  int item;
  
  //    while(1)
   while(bound < 70)
  {
     
    item = produceitem();
    //struct sembuf sb = {1, -1, 0};//down(&empty)//
    //struct sembuf sb1 = {0, -1, 0};//down(&mutex)//
    
    //if (semop(semid, &sb, 1) == -1)//down(&empty)//
    // perror("semop");
       // if (semop(semid, &sb1, 1) == -1)//down(&mutex)//
    // perror("semop");
    down(&empty, 1);
    down(&mutex, 0);

    int index;
    
    index = semctl(semid, 2, GETVAL);//gets value of the countable FULL

      if (buffer[index] == 0)//if it is == 0, then this spot is empty. 
      {
      buffer[index] = item;//inserts random item into index FULL
      printf("\nProducer inserted %d into index %d\n",item, index);
      }
      
      
      // sb1.sem_op = 1;//for up(&mutex)
      // struct sembuf sb3 = {2, 1, 0};//for up(&full)
     
      /* if (semop(semid, &sb1, 1) == -1)//up(&mutex)//
     perror("semop");
     if (semop(semid, &sb3, 1) == -1)//up(&full)//
     perror("semop");*/
      up(&mutex, 0);
      up(&full, 2);
      
     bound++;
  }
  
  pthread_exit(NULL);
}
void *consumer()
{
  int item;
  int bound1;
  // while(1)
  while (bound1 < 70)  
  {
    
    // struct sembuf sb4 = {2, -1, 0};//for down(&full)
    // struct sembuf sb5 = {0, -1, 0};//for down (&mutex)
    // semop(semid, &sb4, 1);
    // semop(semid, &sb5, 1);
    down(&full, 2);
    down(&mutex, 0);

     int index1;

     index1 = semctl(semid, 1, GETVAL);//may be a problem here 
     item = buffer[index1];//problem here...whatever full is.. is what we want                                                                          
     /* sb5.sem_op = 1;//for up(&mutex)
      struct sembuf sb7 = {1, 1, 0};//for up(&empty)
      semop(semid, &sb5, 1);//up(&mutex)
      semop(semid, &sb7, 1);//up(&empty)*/
     up(&mutex, 0);
     up(&empty, 1);
     if (item != 0)//if the item is 0, this is an empty spot in the array
     {
      consumeitem(index1);
      printf("\nConsumer took out %d from index %d\n", item, index1);
     }
     bound1++;
   }
 
  pthread_exit(NULL);
}

void down(semaphore *sem, int index)
{

  /* if (sem != 0)
     sem = sem - 1;*/
  
  // semaphore sem = (int)arg;
   struct sembuf sb = {index, -1, 0};
   semop(semid, &sb, 1);
}
void up(semaphore *sem, int index)
{
  // int index;
  // if (*sem != 0)
  // sem = sem + 1;
  struct sembuf sb1 = {index, 1, 0};
  semop(semid, &sb1, 1);
}

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
struct mymsg 
{
  long messagetype;
  char message[200];
};
int main()
{
  struct mymsg message;
  key_t key;
  key = ftok("msgQsnd.c", 'B');

  int queueid;
  queueid = msgget(key, 0644 | IPC_CREAT);  
  
  printf("Enter two integers, ^D to quit.\n");
  
  //read from stdin until EOF and send numbers stored in message to the queue
  while (gets(message.message), !feof(stdin))
    {
      msgsnd(queueid, (struct message *)&message, sizeof(message), 0);
    }

  
  //remove the message queue
  if (msgctl(queueid, IPC_RMID, NULL)==-1)
    printf("Error Removing queue");
  
  exit(0);
}

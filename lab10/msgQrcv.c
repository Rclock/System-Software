#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
struct message 
{
  long messagetype;
  char message[200];

};
  
int main()
{
  struct message message;
  int queueid;
  key_t key;
  
  key=ftok("msgQsnd.c", 'B');

  queueid = msgget(key, 0644);
  char buffer[20];
  printf("Ready to receive messages\n");
  int int1, int2;
  
  for (;;)
    {
      if ( msgrcv(queueid, (struct message *)&message, sizeof(message), 0 ,0) == -1)
	{
	printf("Done receiving messages.");
        exit(0);
	}
      
      sprintf(buffer, "%s", message.message);

      if (sscanf(buffer, "%d %d", &int1, &int2) == 2)
	{
	    int sum = 0;
	    sum = int1 + int2; 
	    printf("Sum is: %d\n", sum);
	}	
    }
  




  exit (0);
}

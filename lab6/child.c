
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int agrc, char *argv[])
{
    pid_t pid;
    
 int n;
 int sleeptime;
 int exit_code;
 
 n = *argv[2]-'0';//takes command line arguments from exec function
	
	sleeptime= *argv[3]-'0';
	exit_code=37;//sets interesting exit code


	 
	 for (; n> 0; n--)
	 {
	   printf("%s %d\n", argv[1], getpid());//prints the child's own id
	    sleep(sleeptime);
	 }
	 
	exit(exit_code);    
}

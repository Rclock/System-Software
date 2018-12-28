#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
void systemError(char *string)
{
  printf("%s Error!", string);
  exit (1);
}
int main()
{
 
  int filein, fileout;
  
  umask(0);
  if ((filein = open("foo.in", O_RDWR)) == -1)//opens input file
      systemError("open");
  
  if ((fileout = open("foorev.out", O_CREAT|O_RDWR, 0760)) == -1)//opens output file
      systemError("open");
    


  char character;
  int nread, size;
  
  if ((size = lseek(filein, -1, SEEK_END)) == -1)//gets size of for loop bound
	systemError("Seek");
      
  
  char v;
       int i, size1;
      for (i = 0; i <= size; i++)//loops to the size of the file 
       {
	    if (( read(filein, &v, 1)) < 0)//reads byte by byte
	        systemError("read");
	       
	   if (( write(fileout, &v, 1)) < 0)//writes byte by byte
	     systemError("write");
	   
	   if ( (size1 = lseek(filein, -2, SEEK_CUR)) < -1)//moves down from the end one character
	     systemError("seek");
	   
	 }
       printf("\n");
       
  exit (0);
  
}

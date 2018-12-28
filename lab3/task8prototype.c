int palind(int filedes1, int filedes2)
{
  int nread, nread1;
  int a,b;
  char buffer1[1], buffer2[1];
 
  
  int i;
  int size;
  size = lseek(filedes1, 0, SEEK_END);
  lseek(filedes1, 0, SEEK_SET);
lseek(filedes2, 0, SEEK_END);

  
  for (i = 0; i < size; i++)
    {
      if ((read(filedes1, buffer1, 1)) < 0)
	err_system("read");
      
      if ((read(filedes2, buffer2, 1)) < 0)//why not != 1?
	err_system("read");
     
      lseek(filedes2, -2, SEEK_CUR);//add error checking
      
      a=buffer1[0];
      b=buffer2[0];
      printf("Character of a is: %d", a);
      printf("Character of b is: %d", b);
      if (a != b)
      {
	printf("Error, this word is not a palindrome. ");
	return 0;
	exit(1);
      }
      



    }
  return 1;

}

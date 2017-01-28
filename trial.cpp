#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int i=0;
  while(!kbhit())
  if(i==0){
    puts("Press a key!");i++;}
  printf("You pressed '%c'!\n", getchar());
  return 0;
}

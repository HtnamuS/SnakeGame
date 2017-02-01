#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "swap.h"

int main(void)
{
	int i=0,j=3;
	std::cout <<i<<endl<<j<< '\n';
	swap(&i,&j);
	std::cout <<i<<endl<<j<<'\n';
}

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "got.h"
#include <fcntl.h>
#include "swap.h"
#include <chrono>
#include <thread>
#include"getch.h"
#define getoxy gotoxy

// int main(void)
// {
// 	int i=0,j=3;
// 	std::cout <<i<<endl<<j<< '\n';
// 	swap(&i,&j);
// 	std::cout <<i<<endl<<j<<'\n';
// }
int main() {
	system("clear");
	cout<<"Hi";
	gotoxy(0,0);
	char c= getch();
	gotoxy(0,3);
	cout<<c;
}

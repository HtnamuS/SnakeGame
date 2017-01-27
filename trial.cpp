#include<iostream>
#include"getch.h"
#include<time.h>

using namespace std;

void wait_time(int wait_t)
{
	time_t curr=time(NULL);
	time_t nav_t=time(NULL);
	while(1){
		if (nav_t-curr==wait_t) {
			break;
		}
		else
			nav_t=time(NULL);
	}
}

int main()
{
	int i=0;
	while(1){
		cout<<"Hi"<<endl;
		wait_time(1);
	}
}

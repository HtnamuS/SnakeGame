#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "swap.h"
#include <chrono>
#include <thread>

// int main(void)
// {
// 	int i=0,j=3;
// 	std::cout <<i<<endl<<j<< '\n';
// 	swap(&i,&j);
// 	std::cout <<i<<endl<<j<<'\n';
// }
int main() {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
	std::cout<<"Hi"<<endl;
    std::this_thread::sleep_for(seconds(1));
    std::cout<<"10 nanoseconds"<<endl;
    sleep_until(system_clock::now() + seconds(1));
    std::cout<<"1second and 10 nanoseconds"<<endl;
}

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

//#define SHHH

int main(){
    void wakeup(int);
    //模拟sleep(4)
    signal(SIGALRM,wakeup);
    alarm(4);
    pause();
    printf("Morning so sonn?\n");
}

void wakeup(int signum)
{
    #ifndef SHHH
        printf("Alarm received from kernel\n");
    #endif
}
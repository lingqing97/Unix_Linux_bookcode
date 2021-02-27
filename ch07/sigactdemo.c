#include<stdio.h>
#include<signal.h>

#define INPUTLEN 100

void inithandler(int);

void main(){
    struct sigaction newhandler;
    sigset_t   blocked;
    char x[INPUTLEN];


    newhandler.sa_handler =inithandler;
    newhandler.sa_flags = SA_RESTART;

    sigemptyset(&blocked);
    sigaddset(&blocked,SIGQUIT);
    newhandler.sa_mask =blocked;

    if(sigaction(SIGINT,&newhandler,NULL)==-1)
        perror("sigaction");
    else
        while(1){
            fgets(x,INPUTLEN,stdin);
            printf("input: %s",x);
        }
}

void inithandler(int s){
    printf("Called with signal %d\n",s);
    sleep(s);
    printf("done handing signal %d\n",s);
}
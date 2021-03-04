#include<stdio.h>
#include<pthread.h>

#define NUM 5

void* print_msg(void*);

int main()
{
    pthread_t pid1,pid2;
    pthread_create(&pid1,NULL,print_msg,(void*)"hello ");
    pthread_create(&pid2,NULL,print_msg,(void*)"world\n");

    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);

    return 0;
}

void* print_msg(void* msg)
{
    char* cp=(char*) msg;
    int i;
    for(i=0;i<NUM;++i){
        printf("%s",cp);
        fflush(stdout);
        sleep(1);
    }
    return;
}
#include<stdio.h>

int main()
{
    printf("Before fork(),myid is %d\n",getpid());
    fork();
    fork();
    fork();
    sleep(1);
    printf("After fork(),myid is %d\n",getpid());
    return 0;
}
#include<stdio.h>

int main()
{
    printf("Before fork(),myid is %d\n",getpid());
    int result=fork();
    sleep(1);
    printf("After fork(),myid is %d,fork() says:%d\n",getpid(),result);
    return 0;
}
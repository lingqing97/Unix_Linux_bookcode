#include<stdio.h>

#define DELAY 2

void child_node();
void parent_node();

int main(){
    printf("before: mypid is %d\n",getpid());
    int result;
    if((result =fork())==-1)
        perror("fork");
    if(result==0) child_node();
    else parent_node(result);
    return 0;
}

void child_node()
{
    printf("childnode:mypid is %d\n",getpid());
    exit(17);
}

void parent_node(int child_pid)
{
    int state,res;
    res=wait(&state);
    printf("waiting my child %d done,wait result is %d\n",child_pid,res);
    int high_8=state>>8;
    int low_7=state & 0x7F;
    int bit_7=state & 0x80;
    printf("status:exit = %d,sig = %d,core = %d \n",high_8,low_7,bit_7);
}
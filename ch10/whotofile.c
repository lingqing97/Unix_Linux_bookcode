#include<stdio.h>
#include<unistd.h>      //for close()
#include<fcntl.h>       //for creat()

int main()
{
    int pid;
    printf("About to run who into a file\n");
    if((pid==fork())==-1){
        perror("fork");
    }
    if(pid==0){
        close(1);
        creat("userlist",0644);
        execlp("who","who",NULL);
        perror("execlp");
        exit(0);
    }
    else{
        wait(NULL);
        printf("Done running who. results in userlist.\n");
    }
    return 0;
}
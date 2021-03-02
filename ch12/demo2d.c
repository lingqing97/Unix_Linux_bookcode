#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/errno.h>

int make_server_socket(int portnum);
int connect_to_server(char* host,int portnum);

#define PORTNUM 15000
#define oops(msg) { perror(msg); exit(1); }

static int cnt=1;

void process_request(int fd)
{
    if(fork()==0){
        dup2(fd,1);
        close(fd);
        execlp("date","date",NULL);
        oops("execlp");
    }
}

void child_waiter(int signum)
{
    //wait(NULL);
    //同时处理多个SIGCHLD信号
    while(waitpid(-1,NULL,WNOHANG)>0);
}

void main()
{
    int sock_id;
    signal(SIGCHLD,child_waiter);
    sock_id=make_server_socket(PORTNUM);
    if(sock_id==-1)
        oops("make_server_socket");
    while(1)
    {
        int fd=accept(sock_id,NULL,NULL);
        if(fd==-1)
            //过滤信号中断导致的fd=-1
            if(errno==EINTR)
                continue;
            else
                exit(1);
        process_request(fd);
        close(fd);
    }
}
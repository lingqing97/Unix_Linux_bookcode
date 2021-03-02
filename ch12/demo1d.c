#include<stdio.h>
#include<unistd.h>

int make_server_socket(int portnum);
int connect_to_server(char* host,int portnum);

#define PORTNUM 15000
#define oops(msg) { perror(msg); exit(1); }

void process_request(int fd)
{
    int pid=fork();
    switch(pid)
    {
        case -1: return;
        case 0: dup2(fd,1);
                close(fd);
                execlp("date","date",NULL);
                oops("execlp");
        default:wait(NULL);
    }
}

void main()
{
    int sock_id;
    sock_id=make_server_socket(PORTNUM);
    if(sock_id==-1)
        oops("make_server_socket");
    while(1)
    {
        int fd=accept(sock_id,NULL,NULL);
        if(fd==-1)
            exit(1);
        process_request(fd);
        close(fd);
    }
}
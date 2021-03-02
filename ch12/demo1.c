#include<stdio.h>

int make_server_socket(int portnum);
int connect_to_server(char* host,int portnum);

#define PORTNUM 15000
#define oops(msg) { perror(msg); exit(1); }

void talk_with_server(int fd)
{
    char buf[BUFSIZ];
    int n;
    while((n=read(fd,buf,BUFSIZ))>0){
        if(write(1,buf,n)!=n){
            oops("write");
        }
    }
}

void main(int ac,char* av[])
{
    int fd;
    fd=connect_to_server(av[1],PORTNUM);
    if(fd==-1)
        exit(1);
    talk_with_server(fd);
    close(fd);
}

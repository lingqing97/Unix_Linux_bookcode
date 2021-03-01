#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define oops(msg) { perror(msg); exit(1); }

void main(int ac,char* av[])
{
    //step1: Get a socket
    int sock_id=socket(AF_INET,SOCK_STREAM,0);
    if(sock_id==-1)
        oops("socket");

    //step2: connect to server
    struct sockaddr_in servadd;
    struct hostent* hp;
    bzero(&servadd, sizeof(servadd));
    hp=gethostbyname(av[1]);
    if(hp==NULL)
        oops(av[1]);
    bcopy(hp->h_addr,(struct sockaddr*)&servadd.sin_addr,hp->h_length);
    servadd.sin_port=htons(atoi(av[2]));
    servadd.sin_family=AF_INET;
    if(connect(sock_id,(struct address*)&servadd, sizeof(servadd))!=0)
        oops("connect");

    //step3: transfer data from server,then hangup
    char message[BUFSIZ];
    int messlen=read(sock_id,message,BUFSIZ);
    if(messlen==-1)
        oops("read");
    if(write(1,message,messlen)!=messlen)
        oops("write");
    close(sock_id);
}
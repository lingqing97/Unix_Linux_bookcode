#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>

#define oops(msg) { perror(msg); exit(1);}

int make_server_socket(int portnum)
{
    int sock=socket(AF_INET,SOCK_DGRAM,0);
    if(sock==-1) oops("socket");
    struct sockaddr_in addr;
    char hostname[BUFSIZ];
    gethostname(hostname,BUFSIZ);
    make_address(hostname,portnum,&addr);
    if(bind(sock,(struct sockaddr*)&addr,sizeof(addr))!=0)
        oops("bind");
    return sock;
}

int make_client_socket()
{
    return socket(AF_INET,SOCK_DGRAM,0);
}

void make_address(char* hostname,int portnum,struct sockaddr_in* addr)
{
    bzero(addr,sizeof(struct sockaddr_in));
    struct hostent* hp=gethostbyname(hostname);
    if(hp==NULL) oops("gethostbyname");
    bcopy(hp->h_addr,(void*)&addr->sin_addr,hp->h_length);
    addr->sin_port=htons(portnum);
    addr->sin_family=AF_INET;
}

void got_internet_address(char* host,int len,int* portp, struct sockaddr_in* addrp)
{
    strncpy(host,inet_ntoa(addrp->sin_addr),len);
    *portp=ntohs(addrp->sin_port);
}
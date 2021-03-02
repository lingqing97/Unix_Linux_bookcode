#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<time.h>
#include<string.h>


#define HOSTLEN 256
#define BACKLOG 1

int make_server_socket_q(int,int);

int make_server_socket(int portnum)
{
    return make_server_socket_q(portnum,BACKLOG);
}

int make_server_socket_q(int portnum,int backlog)
{
    //step1: Got a socket
    int sock_id=socket(PF_INET, SOCK_STREAM, 0);
    if(sock_id==-1)
        return -1;
    //step2: bind a address and port
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    char hostname[BUFSIZ];
    gethostname(hostname,BUFSIZ);
    struct hostent* hp=gethostbyname(hostname);
    printf("%s",hp->h_addr);
    bcopy((void*)hp->h_addr,(void*)&server_addr.sin_addr,hp->h_length);
    server_addr.sin_port=htons(portnum);
    server_addr.sin_family=AF_INET;
    if(bind(sock_id,(struct sockaddr*)&server_addr, sizeof(server_addr))!=0)
        return -1;
    //step3:listen
    if(listen(sock_id,backlog)!=0)
        return -1;
    return sock_id;
}

int connect_to_server(char* host,int portnum)
{
    //step1: Got a socket
    int sock_id=socket(AF_INET, SOCK_STREAM, 0);
    if(sock_id==-1)
        return -1;
    //step2: connect to a server
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    struct hostent* hp=gethostbyname(host);
    if(hp==NULL)
        return -1;
    bcopy((void*)hp->h_addr,(void*)&addr.sin_addr,hp->h_length);
    addr.sin_port=htons(portnum);
    addr.sin_family=AF_INET;
    if(connect(sock_id,(struct sockaddr*)&addr, sizeof(addr))!=0)
        return -1;
    return sock_id;
}
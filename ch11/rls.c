#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>


#define oops(msg) { write(1,msg,256); exit(1);}
#define PORTNUM 15000   // 端口号

void main(int ac,char* av[])
{
    //step1: Get a socket;
    int sock_id=socket(AF_INET, SOCK_STREAM, 0);
    if(sock_id==-1)
        oops("socket");

    //step2: Connect to server
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));


    struct hostent* hp=gethostbyname(av[1]);
    if(hp==NULL)
        oops(av[1]);
    bcopy(hp->h_addr,(struct sockaddr*)&server_addr.sin_addr,hp->h_length);
    server_addr.sin_port=htons(PORTNUM);
    server_addr.sin_family=AF_INET;

    if(connect(sock_id,(struct sockaddr*)&server_addr,sizeof(server_addr))!=0)
        oops("connect\n");

    //step3: send directory name, then read back results
    if((write(sock_id,av[2],strlen(av[2])))==-1)
        oops("write\n");
    if(write(sock_id,"\n",1)==-1)
        oops("write\n");
    char buffer[BUFSIZ];
    int n_read;
    while((n_read=read(sock_id,buffer,BUFSIZ))>0){
        if(write(1,buffer,n_read)!=n_read)
            oops("write");
    }
    close(sock_id);
}
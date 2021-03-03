#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>

#define oops(msg,x) { perror(msg); exit(x);}

int make_client_socket();
void make_address(char* hostname,int portnum,struct sockaddr_in* addr);
//void got_internet_address(char* host,int len,int* portp, struct sockaddr_in* addrp);

int main(int ac,char* av[])
{
    if(ac!=4){
        fprintf(stderr,"usage: parameter format error\n");
        exit(1);
    }
    int sock=make_client_socket();
    struct sockaddr_in addr;
    make_address(av[1],atoi(av[2]),&addr);
    int port=atoi(av[2]);
    //got_internet_address(av[1],strlen(av[1]),&port,&addr);
    if(sendto(sock,av[3],strlen(av[3]),0,&addr,sizeof(addr))==-1)
        oops("sendto error",2);
    char message[BUFSIZ+BUFSIZ];
    int addrlen=sizeof(addr);
    int msglen=recvfrom(sock,message,BUFSIZ+BUFSIZ,0,&addr, &addrlen);
    if(msglen<=0)
        return 0;
    printf("%s\n",message);
    return 0;
}
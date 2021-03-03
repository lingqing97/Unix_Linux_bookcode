#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define oope(msg,x) { perror(msg); exit(x); }

int make_server_socket(int portnum);
void say_who_called(struct sockaddr_in*);
void got_internet_address(char*,int,int*,struct sockaddr_in*);

int main(int ac,char* av[])
{
    int port;
    if((ac==1 || ((port=atoi(av[1]))<0))){
        fprintf(stderr,"usage: parameter format error");
        exit(1);
    }
    int sock=make_server_socket(port);
    struct sockaddr_in addr;
    char buf[BUFSIZ];
    int msglen;
    int addrlen=sizeof(addr);
    while((msglen=recvfrom(sock,buf,BUFSIZ,0,&addr,&addrlen))>0){
        printf("wait...");
        buf[msglen]='\0';
        printf("dgrecv: got a message:%s \n",buf);
        say_who_called(&addr);
        reply_to_sender(sock,buf,&addr,addrlen);
    }
    return 0;
}

void say_who_called(struct sockaddr_in* addrp)
{
    char host[BUFSIZ];
    int port;
    got_internet_address(host,BUFSIZ,&port,addrp);
    printf("from: %s:%d\n",host,port);
}

void reply_to_sender(int sock,char* buf,struct sockaddr_in* addrp,socklen_t addrlen)
{
    char reply[BUFSIZ+BUFSIZ];
    sprintf(reply,"Thanks for you %d char message\n",strlen(buf));
    sendto(sock,reply,strlen(reply),0,addrp,addrlen);
}
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<time.h>

#define MSGLEN 512
#define oops(m,x) { perror(m);exit(x);}
#define SOCKNAME "/tmp/logfilesock"

int main(int ac,char* av[])
{
    char sockname[]=SOCKNAME;
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, sockname);
    int addrlen=strlen(sockname)+sizeof(addr.sun_family);

    int sock=socket(PF_UNIX,SOCK_DGRAM, 0);
    if(sock==-1)
        oops("socket",2);

    //bind
    if(bind(sock,(struct sockaddr*)&addr,addrlen)==-1)
        oops("bind",3);

    int msgnum=0;
    while(1)
    {
        char msg[MSGLEN];
        int l=read(sock,msg,MSGLEN);
        msg[l]='\0';
        time_t now;
        time(&now);
        char* timestr=ctime(&now);
        timestr[strlen(timestr)-1]='\0';

        printf("[%5d] %s %s \n",msgnum++,timestr,msg);
        fflush(stdout);
    }
}
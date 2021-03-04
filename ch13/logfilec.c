#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

#define SOCKEY "/tmp/logfilesock"
#define oops(m,x) { perror(m); exit(x);}

void main(int ac,char* av[])
{
    if(ac!=2)
    {
        fprintf(stderr,"usage:logfilec 'message'\n");
        exit(1);
    }

    int sock=socket(PF_UNIX,SOCK_DGRAM,0);
    if(sock==-1)
        oops("socket",2);

    struct sockaddr_un addr;
    char sockname[]=SOCKEY;
    addr.sun_family=AF_UNIX;
    strcpy(addr.sun_path,sockname);
    int addrlen=strlen(addr.sun_path)+sizeof(addr.sun_family);

    char* msg=av[1];
    if(sendto(sock,msg,strlen(msg),0,&addr,addrlen)==-1)
        oops("sendto",3);
}
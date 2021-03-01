#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<time.h>

#define PORTNUM 13000   //端口号
#define HOSTLEN 256
#define oops(msg) { perror(msg); exit(1); }

int main(int ac,char* av[])
{
    //step1: ask kernel for a socketco
    int sock_id=socket(PF_INET, SOCK_STREAM, 0);
    if(sock_id==-1)
        oops("socket");

    //step2: bind address to socket. Address is host,port
    struct sockaddr_in saddr;
    bzero((void*)&saddr, sizeof(saddr));
    //获取主机号
    char hostname[HOSTLEN];
    gethostname(hostname, sizeof(hostname));
    struct hostent* hp=gethostbyname(hostname);
    bcopy((void*)hp->h_addr,(void*)&saddr.sin_addr,hp->h_length);
    //设置端口
    saddr.sin_port=htons(PORTNUM);
    saddr.sin_family=AF_INET;       //因特网地址族(AF_INET)使用主机和端口来标志

    if(bind(sock_id,(struct sockaddr*)&saddr,sizeof(saddr))!=0)
        oops("bind")

    //step3: allow incoming calls with Qsize=1 on socket
    if(listen(sock_id,1)!=0)          //这里1指定最大连接数
        oops("listen");

    //main loop:accept(),write(),close()
    while(1){
        int sock_fd=accept(sock_id,NULL,NULL);      //accept阻塞当前进程，直到连接建立
        printf("Wow! got a call!\n");
        if(sock_fd==-1)
            oops("accept");
        FILE* sock_fp=fdopen(sock_fd,"w");
        if(sock_fp==NULL)
            oops("fdopen");
        time_t thetime=time(NULL);

        fprintf(sock_fp,"The time here is..");
        fprintf(sock_fp,"%s",ctime(&thetime));
        fclose(sock_fp);
    }
}
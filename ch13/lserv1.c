#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
#include<sys/errno.h>

#define MSGLEN 128      //Size of our datagrams
#define RECLAIM_INTERVAL 10

void ticket_reclaim(int);

int main(int ac,char* av[])
{
    struct sockaddr_in client_addr;
    socklen_t addrlen=sizeof(client_addr);
    char buf[MSGLEN];
    int ret;
    int sock;

    sock=setup();
    //定义检查进程是否还存在
    signal(SIGALRM,ticket_reclaim);
    alarm(RECLAIM_INTERVAL);

    while(1){
        addrlen=sizeof(client_addr);
        ret=recvfrom(sock,buf,MSGLEN,0,&client_addr,&addrlen);
        if(ret!=-1){
            buf[ret]='\0';
            narrate("GOT:",buf,&client_addr);
            //关闭计时器，防止在处理请求的过程中被中断
            int time_left=alarm(0);
            handle_request(buf,&client_addr,addrlen);
            alarm(time_left);
        }
        else if(errno!=EINTR)
            perror("recvfrom");
    }
}
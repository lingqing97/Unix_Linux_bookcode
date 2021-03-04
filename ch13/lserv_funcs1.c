#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<signal.h>
#include<sys/errno.h>

#define SERVER_PORTNUM 2020             //Our server's port number
#define MSGLEN 128                      //Size of our datagram
#define TICKET_AVAIL 0                  //Slot is available for use
#define MAXUSERS 3                      //Only 3 users for us
#define oops(x) { perror(x); exit(-1);}

int ticket_array[MAXUSERS];             //Our ticker array
int sd=-1;                              //Our socket
int num_tickets_out=0;                  //Number of tickets outstanding

char* do_hello();
char* do_goodbye();

int setup()
{
    sd=make_server_socket(SERVER_PORTNUM);
    if(sd==-1)
        oops("make socket");
    free_all_tickets();
    return sd;
}

void free_all_tickets()
{
    int i;
    for(i=0;i<MAXUSERS;++i)
        ticket_array[i]=TICKET_AVAIL;
}

void shut_down()
{
    close(sd);
}

char* do_validate(char* msg);

void handle_request(char* req,struct sockaddr_in* client,socklen_t addlen)
{
    char* response;
    int ret;

    if(strncmp(req,"HELO",4)==0)
        response=do_hello(req);
    else if(strncmp(req,"GBYE",4)==0)
        response=do_goodbye(req);
    else if(strncmp(req,"VALID",4)==0)
        response=do_validate(req);
    else
        response="FAIL invalid request";
    narrate("SAID:",response,client);
    ret=sendto(sd,response,strlen(response),0,client,addlen);
    if(ret==-1)
        perror("SERVER sendto failed");
}

char* do_hello(char* msg_p)
{
    int x;
    static char replybuf[MSGLEN];

    if(num_tickets_out>=MAXUSERS)
        return "FAIL no tickets available";

    for(x=0;x<MAXUSERS&&ticket_array[x]!=TICKET_AVAIL;++x);

    if(x==MAXUSERS){
        narrate("database corrupt","",NULL);
        return "FAIL database corrupt";
    }

    ticket_array[x]=atoi(msg_p+5);
    sprintf(replybuf,"TICK %d. %d",ticket_array[x],x);
    num_tickets_out++;
    return replybuf;
}

char* do_goodbye(char* msg_p)
{
    int pid,slot;

    if((sscanf(msg_p+5,"%d. %d",&pid,&slot)!=2)||(ticket_array[slot]!=pid)){
        narrate("Bogus ticket",msg_p+5,NULL);
        return "FAIL invalid ticket";
    }

    ticket_array[slot]=TICKET_AVAIL;
    num_tickets_out--;

    return "THNX See ya!";
}

char* do_validate(char* msg)
{
    int pid,slot;
    if(sscanf(msg+5,"%d. %d",&pid,&slot)==2 && ticket_array[slot]==pid)
        return "GOOD Valid ticket";

    //bad ticket
    narrate("Bogus ticket",msg+5,NULL);
    return "FAIL invalid ticket";
}

void narrate(char* msg1,char* msg2,struct sockaddr_in* clientp)
{
    fprintf(stderr,"\t\tSERVER: %s %s",msg1,msg2);

    /*
    if(clientp)
        fprintf(stderr,"(%s:%d)",inet_ntoa(clientp->sin_addr),ntohs(clientp->sin_port));
    */

    putc('\n',stderr);
}

#define RECLAIM_INTERVAL 10

void ticket_reclaim(int signum)
{
    int i;
    char tick[BUFSIZ];

    for(i=0;i<MAXUSERS;++i)
    {
        //给进程发送编号为0的信号确定它是否存在，若进程不存在，内核将不会发送信号，而是返回错误并设置errno为ESRCH
        if((ticket_array[i]!=TICKET_AVAIL) && (kill(ticket_array[i],0)==-1) && (errno == ESRCH)){
            sprintf(tick,"%d. %d",ticket_array[i],i);
            narrate("freeing",tick,NULL);
            ticket_array[i]=TICKET_AVAIL;
            num_tickets_out--;
        }
    }
    alarm(RECLAIM_INTERVAL);        //reset alarm clock
}
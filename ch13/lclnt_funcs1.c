#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>

static int pid=-1;                      //Our pid
static int sd=-1;                       //Our communication socket
static struct sockaddr serv_addr;       //Server address
static socklen_t serv_alen;             //Length of address
static char ticket_buf[128];            //Buffer to hold our ticket
static int have_ticket=0;               //Set when we have a ticket

#define MESLEN  128                     //Size of our datagrams
#define SERVER_PORTNUM 2020             //Our server's port number
#define HOSTLEN 512
#define oops(p) { perror(p);exit(1);}


//function declare
char* do_transaction();

void setup()
{
    char hostname[BUFSIZ];
    pid=getpid();                       //for ticks and msgs
    sd=make_client_socket();      //to talk to server
    if(sd==-1)
        oops("Cannot create socket");
    gethostname(hostname,HOSTLEN);
    make_address(hostname,SERVER_PORTNUM,&serv_addr);
    serv_alen=sizeof(serv_addr);
}

void shut_down()
{
    close(sd);
}

int get_ticket()
{
    char* response;
    char buf[MESLEN];
    if(have_ticket)
        return 0;

    sprintf(buf,"HELO %d",pid);
    if((response=do_transaction(buf))==NULL)
        return -1;

    if(strncmp(response,"TICK",4)==0){
        strcpy(ticket_buf,response+5);
        have_ticket=1;
        narrate("got ticket",ticket_buf);
        return 0;
    }
    if(strncmp(response,"FAIL",4)==0)
        narrate("Could not get ticket",response);
    else
        narrate("Unknown message:",response);
    return -1;
}

int release_ticket()
{
    char buf[MESLEN];
    char* response;

    if(!have_ticket)
        return 0;

    sprintf(buf,"GBYE %s",ticket_buf);
    if((response=do_transaction(buf))==NULL)
        return -1;
    if(strncmp(response,"THNX",4)==0){
        narrate("released ticket OK","");
        return 0;
    }
    if(strncmp(response,"FAIL",4)==0)
        narrate("release failed",response+5);
    else
        narrate("Unknown message:",response);
    return -1;
}

char* do_transaction(char* msg)
{
    static char buf[MESLEN];
    struct sockaddr retaddr;
    socklen_t addrlen=sizeof(retaddr);

    int ret=sendto(sd,msg,strlen(msg),0,&serv_addr,serv_alen);
    if(ret==-1){
        syserr("sendto");
        return NULL;
    }

    ret=recvfrom(sd,buf,MESLEN,0,&retaddr,&addrlen);
    if(ret==-1){
        syserr("recvfrom");
        return NULL;
    }

    return buf;
}

void narrate(char* msg1,char* msg2)
{
    fprintf(stderr,"CLIENT [ %d ]: %s %s\n",pid,msg1,msg2);
}

void syserr(char* msg1)
{
    char buf[MESLEN];
    sprintf(buf,"CLIENT [ %d ]: %s",pid,msg1);
    perror(buf);
}

int validate_ticket()
{
	char *response;
	char buf[MESLEN];

	if(!have_ticket)			/* bizarre */
		return(0);

	sprintf(buf, "VALD %s", ticket_buf);	/* compose request	*/

	if ( (response = do_transaction(buf)) == NULL )
		return(-1);

	narrate("Validated ticket: ", response);

	if ( strncmp(response, "GOOD", 4) == 0 )
		return(0);

	if ( strncmp(response,"FAIL",4) == 0){
		have_ticket = 0;
		return(-1);
	}
	narrate("Unknown message:", response);

	return(-1);
}
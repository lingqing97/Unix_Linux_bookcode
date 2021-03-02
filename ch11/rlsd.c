#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<time.h>
#include<string.h>


#define PORTNUM 15000   // 端口号
#define HOSTLEN 256
#define oops(msg)  { perror(msg); exit(1);}

void sanitize(char*);

int main(int ac,char* av[])
{
    //step1: ask kernel for a socket
    int sock_id=socket(PF_INET,SOCK_STREAM,0);
    if(sock_id==-1)
        oops("socket\n");

    //step2: bind address to socket.Address is host,port
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    char hostname[HOSTLEN];
    gethostname(hostname,HOSTLEN);
    struct hostent* hp=gethostbyname(hostname);
    if(hp==NULL)
        oops("gethostbyname\n");
    bcopy(hp->h_addr,(struct sockaddr*)&addr.sin_addr,hp->h_length);
    addr.sin_port=htons(PORTNUM);
    addr.sin_family=AF_INET;
    if(bind(sock_id,(struct sockaddr*)&addr,sizeof(addr))!=0)
        oops("bind\n");

    //step3: allow incoming calls with Qsize=1 on socket
    if(listen(sock_id,1)!=0)
        oops("listen\n");


    //main loop: accept(),write(),close()
    while(1){
        int sock_fd=accept(sock_id,NULL,NULL);
        if(sock_fd==-1)
            oops("accept\n");
        FILE *sock_fpi,*sock_fpo;
        if((sock_fpi=fdopen(sock_fd,"r"))==NULL)
            oops("fdopen reading\n");

        char dirname[BUFSIZ];
        if(fgets(dirname,BUFSIZ-5,sock_fpi)==NULL)
            oops("reading dirname\n");

        //dirname检查
        sanitize(dirname);

        if((sock_fpo=fdopen(sock_fd,"w"))==NULL)
            oops("fdopen writing\n");
        char command[BUFSIZ];
        sprintf(command,"ls %s",dirname);
        FILE* pipe_fp;
        if((pipe_fp=popen(command,"r"))==NULL)
            oops("popen\n");
        int c;
        while((c=getc(pipe_fp))!=EOF)
            putc(c,sock_fpo);
        pclose(pipe_fp);
        fclose(sock_fpo);
        fclose(sock_fpi);
    }
}

void sanitize(char* str)
{
    char* src,*dest;
    for(src=dest=str;*src;src++)
        if(*src=='/' || isalnum(*src))
            *dest++=*src;
    *dest='\0';
}

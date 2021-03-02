#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>

int make_server_socket(int portnum);
void read_til_crnl(FILE *);
void process_rq(char*,int);

void main(int ac,char* av[])
{
    if(ac==1){
        fprintf(stderr,"usage: ws portnum\n");
        exit(1);
    }
    int sock=make_server_socket(atoi(av[1]));
    if(sock==-1) exit(2);

    //main loop here
    fprintf(stdin,"doing main loop...");
    while(1){
        int fd=accept(sock,NULL,NULL);
        FILE* fpin=fdopen(fd,"r");
        //read request
        char request[BUFSIZ];
        fgets(request,BUFSIZ,fpin);
        printf("got a call: request=%s",request);
        read_til_crnl(fpin);

        //do what client asks
        process_rq(request,fd);
        fclose(fpin);
    }
}

void read_til_crnl(FILE* fp)
{
    char buf[BUFSIZ];
    while(fgets(buf,BUFSIZ,fp)!=NULL && strcmp(buf,"\r\n")!=0);
}


//函数声明
void cannot_do(int);
int not_exist(char*);
void do_404(char*,int);
int isadir(char*);
void do_ls(char*,int);
int ends_in_cgi(char*);
void do_exec(char*,int);
void do_cat(char*,int);


//rq is HTTP command: GET /foo/bar.html HTTP/1.0
void process_rq(char* rq,int fd)
{
    char cmd[BUFSIZ],arg[BUFSIZ];
    //!!!
    if(fork()!=0)
        return;
    strcpy(arg,"./");
    if(sscanf(rq,"%s %s",cmd,arg+2)!=2)
        return;

    if(strcmp(cmd,"GET")!=0)
        cannot_do(fd);
    else if(not_exist(arg))
        do_404(arg,fd);
    else if(isadir(arg))
        do_ls(arg,fd);
    else if(ends_in_cgi(arg))
        do_exec(arg,fd);
    else
        do_cat(arg,fd);
}

void header(FILE* fp,char* content_type)
{
    fprintf(fp,"HTTP/1.0 200 OK\r\n");
    if(content_type)
        fprintf(fp,"Content-type:%s\r\n",content_type);
}

void cannot_do(int fd)
{
    FILE* fp=fdopen(fd,"w");

    fprintf(fp,"HTTP/1.0 501 Not Implemented\r\n");
    fprintf(fp,"Content-type:text/plain\r\n");
    fprintf(fp,"\r\n");

    fprintf(fp,"That command is not yet implemented\r\n");
    fclose(fp);
}

int not_exist(char* f)
{
    struct stat info;
    return (stat(f,&info)==-1);
}

void do_404(char* item,int fd)
{
    FILE* fp=fdopen(fd,"w");

    fprintf(fp,"HTTP/1.0 404 Not Found\r\n");
    fprintf(fp,"Content-type:text/plain\r\n");
    fprintf(fp,"\r\n");

    fprintf(fp,"The item you requested: %s \r\nis not found\r\n",item);
    fclose(fp);
}

int isadir(char* f)
{
    struct stat info;
    return (stat(f,&info)!=-1 && S_ISDIR(info.st_mode));
}

void do_ls(char* dir,int fd)
{
    FILE* fp;
    fp=fdopen(fd,"w");
    header(fp,"text/plain");
    fprintf(fp,"\r\n");
    fflush(fp);

    dup2(fd,1);
    dup2(fd,2);
    close(fd);
    execlp("ls","ls","-l",dir,NULL);
    perror(dir);
    exit(1);
}

char* file_type(char* f)
{
    char* cp;
    if((cp=strchr(f,'.'))!=NULL)
        return cp+1;
    return "";
}

int ends_in_cgi(char* f)
{
    return (strcmp(file_type(f),"cgi")==0);
}

void do_exec(char* prog,int fd)
{
    FILE* fp;
    fp=fopen(fd,"w");
    header(fp,NULL);
    fflush(fp);
    dup2(fd,1);
    dup2(fd,2);
    close(fd);
    execl(prog,prog,NULL);
    perror(prog);
}

void do_cat(char* f,int fd)
{
    char* content="text/plain";
    char* extension=file_type(f);
    if(strcmp(extension,"html")==0)
        content="text/html";
    else if(strcmp(extension,"gif")==0)
        content="image/gif";
    else if(strcmp(extension,"jpg")==0)
        content="image/jpeg";
    else if(strcmp(extension,"jpeg")==0)
        content="image/jpeg";
    FILE *fpsock,*fpfile;
    fpsock=fdopen(fd,"w");      //将socket文件描述符转为FILE*
    fpfile=fopen(f,"r");        //读取f指向的文件
    if(fpsock!=NULL && fpfile !=NULL)
    {
        header(fpsock,content);
        fprintf(fpsock,"\r\n");
        int c;
        while(c=getc(fpfile)!=EOF)
            putc(c,fpsock);
        fclose(fpfile);
        fclose(fpsock);
    }
    exit(0);
}

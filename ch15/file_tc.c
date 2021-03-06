#include<stdio.h>
#include<sys/file.h>
#include<fcntl.h>

#define oops(m,x) { perror(m); exit(x); }
#define BUFLEN 10

void main(int ac,char* av[])
{
    if(ac!=2){
        fprintf(stderr,"usage: file_tc filename\n");
        exit(1);
    }
    int fd;
    if((fd=open(av[1],O_RDONLY))==-1)
        oops(av[1],3);

    lock_operation(fd,F_RDLCK);
    int nread;
    char buf[BUFLEN];
    while((nread=read(fd,buf,BUFLEN))>0)
        write(1,buf,nread);

    lock_operation(fd,F_UNLCK);
    close(fd);
}

void lock_operation(int fd,int op)
{
    struct flock lock;

    lock.l_start=lock.l_len=0;
    lock.l_whence=SEEK_SET;
    lock.l_pid=getpid();
    lock.l_type=op;

    if(fcntl(fd,F_SETLKW,&lock)==-1)
        oops("lock operation",6);
}
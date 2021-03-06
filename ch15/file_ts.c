#include<stdio.h>
#include<sys/file.h>
#include<fcntl.h>
#include<time.h>

#define oops(m,x)  { perror(m); exit(x); }

void main(int ac,char* av[])
{
    if(ac!=2){
        fprintf(stderr,"usage:file_ts filename\n");
        exit(1);
    }

    int fd;
    if((fd=open(av[1],O_CREAT | O_TRUNC | O_WRONLY,0644))==-1)
        oops(av[1],2);

    time_t now;
    while(1){
        time(&now);
        char* message=ctime(&now);

        lock_operation(fd,F_WRLCK);

        if(lseek(fd,0L,SEEK_SET)==-1)
            oops("lseek",3);
        if(write(fd,message,strlen(message))==-1)
            oops("write",4);

        lock_operation(fd,F_UNLCK);
        sleep(1);
    }
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
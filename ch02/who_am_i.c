#include<stdio.h>
#include<fcntl.h>    //for open() and creat()
#include<unistd.h>   //for read() and write()
#include<time.h>     //for ctime()
#include<utmp.h>     //for struct utmp


#define SHOWHOST

//函数声明
void show_time(long);
void show_info(struct utmp*);
char* whats_my_line(int);


int main(int ac,char* av[]){
    char* myline=NULL;      //终端设备名称
    myline=whats_my_line(0);

    int fd_utmp=-1;
    if((fd_utmp=open(UTMP_FILE,O_RDONLY))==-1){
        perror(UTMP_FILE);
        exit(1);
    }

    struct utmp utbuf;
    while(read(fd_utmp,&utbuf,sizeof(utbuf))==sizeof(utbuf)){
        // printf("%s \n",utbuf.ut_line);
        if(myline==NULL || strcmp(utbuf.ut_line,myline)==0)
            show_info(&utbuf);
    }
    close(fd_utmp);

    return 0;
}

char* whats_my_line(int fd){
    char* rv;
    if(rv=ttyname(0))
        if(strncmp(rv,"/dev/",5)==0)
            rv+=5;
    return rv;
}

void show_info(struct utmp* utp){
    //为在线的用户信息不打印
    if(utp->ut_type!=USER_PROCESS) return;
    printf("%-8.8s",utp->ut_user);      //the logname
    printf(" ");
    printf("%-8.8s",utp->ut_line);      //the tty
    printf(" ");
    show_time(utp->ut_time);            //the log time
    #ifdef SHOWHOST
    if(utp->ut_host[0]!='\0')
        printf("(%s)",utp->ut_host);    //the host
    #endif
    printf("\n");
}

void show_time(long timeval){
    char *cp;
    cp=ctime(&timeval);
    //cp="Tue Feb 23 09:25"
    printf("%12.16s",cp+4);
}
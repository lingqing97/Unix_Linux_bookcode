#include<stdio.h>
#include<utmp.h>    //for utmp struct
#include<fcntl.h>   //for open()
#include<unistd.h>  //for close() and read()
#include<time.h>

#define SHOWHOST

//函数声明
void show_time(long);            //显示标准格式时间
void show_info(struct utmp *);   //显示who输出信息

int main(){
    int* fp;
    //打开utmp文件
    if((fp=open(UTMP_FILE,O_RDONLY))==-1){
        perror(UTMP_FILE);
        exit(1);
    }
    //读取utmp文件内容
    struct utmp utp;
    while(read(fp,&utp,sizeof(utp))==sizeof(utp)){
        show_info(&utp);
    }
    close(fp);
    return 0;
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

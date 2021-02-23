#include<stdio.h>
#include<fcntl.h>    //for open() and creat()
#include<unistd.h>   //for read() and write()
#include<time.h>     //for ctime()
#include<utmp.h>     //for struct utmp

#define BUF_NUM 16   //定义缓冲区数量
#define BUF_SIZE (sizeof(struct utmp))  //定义缓冲区单位大小
#define NULLUTP ((struct utmp*)NULL)

#define SHOWHOST
#define ACTIVE_ONLY

//函数声明
void show_time(long);
void show_info(struct utmp*);

static char utmpbuf[BUF_NUM*BUF_SIZE];  //缓冲区大小
static int  num_recs;                   //缓冲区总存量
static int  cur_rec;                    //当前已使用缓冲区个数
static int  fd_utmp=-1;                 //utmp文件的文件描述符

//打开utmp文件
int utmp_open(char* filename){
    fd_utmp=open(filename,O_RDONLY);
    num_recs=cur_rec=0;
    return fd_utmp;
}

//申请更多缓冲区
int utmp_reload(){
    int amt_read;
    amt_read=read(fd_utmp,&utmpbuf,BUF_NUM*BUF_SIZE);
    num_recs=amt_read/BUF_SIZE;
    cur_rec=0;
    return num_recs;
}

//读取下一个数据
struct utmp* utmp_next()
{
    struct utmp* recp;
    if(fd_utmp==-1)
        return NULLUTP;
    //当缓冲区全部用完后，重新申请
    //若申请为0，表示读取utmp完毕
    while(1){
        if(cur_rec==num_recs&&utmp_reload()==0)
            return NULLUTP;
        recp=(struct utmp*)&utmpbuf[cur_rec*BUF_SIZE];
        ++cur_rec;
        #ifdef ACTIVE_ONLY
        if(recp->ut_type==USER_PROCESS)
        #endif
            return recp;
    }
    return NULLUTP;
}

//关闭utmp文件
void utmp_close(){
    if(fd_utmp!=-1)
        close(fd_utmp);
}

int main(){
    if(utmp_open(UTMP_FILE)==-1){
        perror(UTMP_FILE);
        exit(1);
    }
    struct utmp* utbufp;
    while((utbufp=utmp_next())!=(struct utmp*)NULL)
        show_info(utbufp);
    utmp_close();
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
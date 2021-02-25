#include<stdio.h>
#include<termios.h>       //for struct termios
#include<fcntl.h>         //for fcntl()
#include<signal.h>        //for signal()

#define ASK "Do you want another transaction"
#define TRIES 3
#define SLEEPTIME 2
#define BEER puchar('\a')

void crtl_c_handler(int);
void tty_mode(int);
void set_necho_mode();
void set_ndelay_mode();
int get_response(char*,int);
char get_ok_response();


int main(){
    //记录初始状态
    tty_mode(0);
    set_necho_mode();
    set_ndelay_mode();
    signal(SIGINT,crtl_c_handler);      //初始crtl_c信号
    signal(SIGQUIT,SIG_IGN);            //忽略crtl /信号
    int response=get_response(ASK,TRIES);
    //恢复初始状态
    tty_mode(1);
    return response;
}

int get_response(char* question,int maxtime){
    printf("%s(y/n)?\n",question);
    fflush(stdout);     //强制输出缓冲区更新
    while(1){   //while循环的等待时间未SLEEP*maxtime
        sleep(SLEEPTIME);
        char input=tolower(get_ok_response());
        if(input=='y') {
            printf("YES\n");
            return 0;
        }
        if(input=='n') {
            printf("NO\n");
            return 1;
        }
        if(maxtime--==0) {
            printf("TIME OUT\n");
            return 2;
        }
    }
}

char get_ok_response(){
    int c;
    //strchr(str,ch)在str中查找ch第一次出现的位置
    while((c=getchar())!=EOF && strchr("yYnN",c)==NULL);    //由于打开了非阻塞标记，所以若无输入会退出循环
    return c;
}

void set_ndelay_mode(){
    //打开非阻塞标记
    int flag=fcntl(0,F_GETFL);
    flag |= O_NDELAY;
    fcntl(0,F_SETFL,flag);
}

void set_necho_mode(){
    //关闭回显模式
    //开启char-by-char模式
    struct termios termios_buf;
    tcgetattr(0, &termios_buf);
    termios_buf.c_lflag &=~ICANON;  //关闭规范输出：即关闭缓冲和编辑功能
    termios_buf.c_cc[VMIN]=1;       //每次读取一个字符,和关闭缓冲一起使用,可以设置其他数
    //所谓回显：是将键盘上的输入显示到标准输出中，关闭回显，进程的输出还是会正常输出
    termios_buf.c_lflag &=~ECHO;    //关闭回显功能
    tcsetattr(0,TCSANOW,&termios_buf);
}

void tty_mode(int how){
    static struct termios original_termios;
    static int original_flag;
    static int store=0;
    if(how==0){
        tcgetattr(0,&original_termios);
        original_flag=fcntl(0,F_GETFL);
        store=1;
    }
    else if(store==1){
        tcsetattr(0,TCSANOW,&original_termios);
        fcntl(0,F_SETFL,original_flag);
    }
}

void crtl_c_handler(int signum){
    tty_mode(signum);
    exit(1);
}
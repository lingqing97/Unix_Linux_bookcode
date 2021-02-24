#include<stdio.h>
#include<termios.h>     //for struct termios

//显示终端的回显位的状态
int echostate(){
    struct termios ter_buf;
    //文件描述符0表示标注输入
    if(tcgetattr(0,&ter_buf)==-1){
        perror("tcgetattr");
        exit(1);
    }
    if(ter_buf.c_lflag & ECHO)
        printf("echo is on,since its bits is 1\n");
    else
        printf("echo is off,since its bits is 0\n");

    return 0;
}

//改变终端的回显位的状态
int echoset(int ac,char* av[]){
    if(ac==1) exit(1);
    struct termios ter_buf;
    //读取状态位
    if(tcgetattr(0,&ter_buf)==-1){
        perror("tcgetattr");
        exit(1);
    }
    //修改状态位
    if(av[1][0]=='y'){
        //置位
        ter_buf.c_lflag |=ECHO;
    }
    else
        //清除位
        ter_buf.c_lflag &=~ECHO;
    //写回状态位
    if(tcsetattr(0,TCSANOW,&ter_buf)==-1){
        perror("tcsetattr");
        exit(1);
    }
    return 0;
}

int main(int ac,char* av[]){
    echoset(ac,av);
    echostate();
    return 0;
}
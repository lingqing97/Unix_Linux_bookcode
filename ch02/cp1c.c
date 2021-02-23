#include<stdio.h>
#include<fcntl.h>    //for open() and creat()
#include<unistd.h>   //for close() and read()

#define BUFSIZE 4096    //声明缓冲区大小
#define FMODE 0644      //声明创建的文件权限

//声明打印错误信息的函数
void oop(char* ,char*);

int main(int ac,char* av[]){

    //参数数量检查
    if(ac!=3){
        fprintf(stderr,"usage: %s source destination\n",*av);
        exit(1);
    }

    //判断源文件和目标文件是否相同
    if(strcmp(av[1],av[2])==0){
        fprintf(stderr,"cp: %s and %s are the same file. \n",av[1],av[2]);
        exit(1);
    }

    //打开源文件
    int source_fp;
    if((source_fp=open(av[1],O_RDONLY))==-1){
        oop("open file error",av[1]);
    }

    //创建目标文件
    int taget_fp;
    if((taget_fp=creat(av[2],FMODE))==-1){
        oop("creat file error",av[2]);
    }

    //复制源文件到目标文件
    char buf[BUFSIZE];
    int n_char;
    while((n_char=read(source_fp,&buf,BUFSIZE))>0){
        if((write(taget_fp,&buf,n_char))!=n_char)
            oop("write file error",av[2]);
    }

    //关闭文件
    if(close(source_fp)==-1||close(taget_fp)==-1){
        oop("close file error",av[0]);
    }

    return 0;
}

void oop(char* error,char* filename){
    fprintf(stderr,"usage: %s",error);
    perror(filename);
    exit(1);
}

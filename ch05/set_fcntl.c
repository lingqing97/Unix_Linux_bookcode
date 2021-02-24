#include<stdio.h>
#include<fcntl.h>   //for fcntl()

//关闭文件描述符的缓冲
int set_sync(){
    int fd=open("test.txt",O_RDONLY);
    if(fd==-1){
        perror("open file error");
        exit(1);
    }
    int s=fcntl(fd,F_GETFL);
    s |= O_SYNC;
    if(fcntl(fd,F_SETFL,s)==-1){
        perror("setting SYNC");
        exit(1);
    }
    //判断是否设置成功
    if(fcntl(fd,F_GETFL) & O_SYNC)
        printf("set SYNC to 1.\n");
    else
        printf("set SYNC to 0.\n");
    close(fd);

    return 0;
}

//启动自动添加模式
//自动添加模式：每次对write的调用前先自动调用lseek，且内核将lseek和write组合成一个原子操作
int set_append(){
    int fd=open("test.txt",O_RDONLY);
    if(fd==-1){
        perror("open file error");
        exit(1);
    }
    int s=fcntl(fd,F_GETFL);
    s |= O_APPEND;
    if(fcntl(fd,F_SETFL,s)==-1){
        perror("setting APPEND");
        exit(1);
    }
    //判断是否设置成功
    if(fcntl(fd,F_GETFL) & O_APPEND)
        printf("set APPEND to 1.\n");
    else
        printf("set APPEND to 0.\n");
    close(fd);
}

int main(){
    set_sync();
    set_append();
    return 0;
}
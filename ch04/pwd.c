#include<stdio.h>
#include<sys/stat.h>    //for stat()
#include<dirent.h>      //for struct dirent
#include<unistd.h>      //for chdir()

#define BUFSIZE 1024

int get_node(char*);
void print_path_to(ino_t);
void inum_to_name(ino_t,char*,int);

int main(){
    print_path_to(get_node("."));
    printf("\n");
    return 0;
}

//打印路径
//实现方法：递归遍历目录树
void print_path_to(ino_t this_node){
    // printf("this_node:%d\n",this_node);
    char this_name[BUFSIZE];
    //递归打印路径
    if(get_node("..")!=this_node){
        chdir("..");
        //根据inode-id获取文件名
        inum_to_name(this_node,this_name,BUFSIZE);
        ino_t next_node=get_node(".");
        // printf("next_node:%d",next_node);
        print_path_to(next_node);
        printf("/%s",this_name);
    }
}

//通过inode-id获取文件名
//实现方法:通过readdir()获得文件名
void inum_to_name(ino_t this_node,char* filename,int buf_len){
    //打开目录
    DIR* dp;
    if((dp=opendir("."))==NULL){
        perror("opendir");
        exit(1);
    }
    //读取目录内容
    struct dirent* dir_buf;
    while((dir_buf=readdir(dp))!=NULL){
        //找到当前目录"."
        if(dir_buf->d_ino==this_node){
            strncpy(filename,dir_buf->d_name,buf_len);
            filename[buf_len-1]='\0';
            closedir(dp);
            return;
        }
    }
}

//获取文件的inode-id
//实现方法：通过stat()获取文件的inode-id信息
int get_node(char* filename){
    struct stat stat_buf;
    if(stat(filename, &stat_buf)==-1){
        perror(filename);
        exit(1);
    }
    return stat_buf.st_ino;
}
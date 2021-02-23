#include<stdio.h>   //opendir() and readdir()
#include<dirent.h>  //struct dirent

//函数声明
void do_ls(char[]);

int main(int ac,char* av[]){
    if(ac==1){
        do_ls(".");
    }
    else{
        while(--ac){
            printf("%s:\n",*++av);
            do_ls(*av);
        }
    }
}

void do_ls(char dirname[]){
    DIR* dp;
    struct dirent* dirbufp;
    if((dp=opendir(dirname))==NULL){
        fprintf(stderr,"ls1: cannot open %s \n",dirname);
    }
    else{
        while((dirbufp=readdir(dp))!=NULL){
            printf("%s\n",dirbufp->d_name);
        }
        closedir(dp);
    }
}
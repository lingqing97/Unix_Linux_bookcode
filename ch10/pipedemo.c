#include<stdio.h>
#include<unistd.h>  //for pipe() write()

int main()
{
    int fildes[2];
    if(pipe(fildes)==-1){
        perror("pipe");
        exit(1);
    }
    printf("Got a pipe. It is file descriptors:{%d,%d}\n",fildes[0],fildes[1]);

    char buf[BUFSIZ];
    while(fgets(buf,BUFSIZ,stdin)!=NULL){
        int len=strlen(buf);
        if(write(fildes[1],buf,len)!=len){
            perror("write to buf");
            exit(1);
        }
        int i;
        for(i=0;i<len;++i)
            buf[i]='X';
        len=read(fildes[0],buf,BUFSIZ);
        if(len==-1){
            perror("read from buf");
            exit(1);
        }
        if(write(1,buf,len)!=len){
            perror("write to stdout");
            exit(1);
        }
    }
    return 0;
}


#include<stdio.h>
#include<unistd.h>  //for close() and dup()
#include<fcntl.h>   //for open()

//#define CLOSE_DUP

int main()
{
    char line[100];

    fgets(line,100,stdin); printf("%s\n",line);
    fgets(line,100,stdin); printf("%s\n",line);
    fgets(line,100,stdin); printf("%s\n",line);

    //open(fd)..close(0)..dup(fd)..close(fd)
    int fd;
    if((fd=open("/etc/passwd",O_RDONLY))==-1)
        perror("open");

    #ifndef CLOSE_DUP
        close(0);
        if(dup(fd)==-1)
            perror("dup");
    #else
        dup2(fd,0);
    #endif

    close(fd);

    fgets(line,100,stdin); printf("%s\n",line);
    fgets(line,100,stdin); printf("%s\n",line);
    fgets(line,100,stdin); printf("%s\n",line);

    return 0;
}
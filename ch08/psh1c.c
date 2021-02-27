#include<stdio.h>
#include<signal.h>
#include<string.h>  //for strcpy()


#define MAXARGS 20
#define ARGLEN 100

char* makestring();

int main()
{
    char *arglist[MAXARGS+1];
    int numargs;
    char argbuf[ARGLEN];
    numargs =0;
    while(numargs < MAXARGS)
    {
        printf("Arg[%d]?",numargs);
        if(fgets(argbuf,ARGLEN,stdin) && *argbuf!='\n')
            arglist[numargs++]=makestring(argbuf);
        else{
            if(numargs>0){
                arglist[numargs]=NULL;
                execute(arglist);
                numargs=0;
            }
        }
    }
    return 0;
}

int execute(char* arglist[])
{
    printf("%s",arglist[0]);
    execvp(arglist[0],arglist);
    perror("execvp failed");
    exit(1);
}

char* makestring(char* buf)
{
    buf[strlen(buf)-1]='\0';     //将'\n'替换为'\0'
    char* cp=malloc(strlen(buf)+1);
    if(cp==NULL){
        fprintf(stderr,"no memory\n");
        exit(1);
    }
    strcpy(cp,buf);
    return cp;
}
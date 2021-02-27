#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAXARGS 20
#define ARGLEN 100

char* makestr(char*);
void execute(char* arglist[]);

int main(){
    char* arglist[MAXARGS];
    char argbuf[ARGLEN];
    int numarg=0;
    while(numarg<MAXARGS){
        printf("Arg[%d]?",numarg);
        if(fgets(argbuf,ARGLEN,stdin)&&*argbuf !='\n')
            arglist[numarg++]=makestr(argbuf);
        else{
            if(numarg>0){
                arglist[numarg]=NULL;
                execute(arglist);
                numarg=0;
            }
        }
    }
    return 0;
}

void execute(char* arglist[])
{
    int pid=fork();
    int existstate;
    switch(pid){
        case -1: perror("fork"); exit(1);
        case 0:
            execvp(arglist[0],arglist);
            perror("execvp failed");
            exit(1);
        default:
            while(wait(&existstate)!=pid);
            printf("child exited with status %d,%d\n",existstate>>8,existstate&0377);   //0377: 00000000 11111111
    }
}

char* makestr(char* argbuf)
{
    argbuf[strlen(argbuf)-1]='\0';
    char* newbuf=malloc(strlen(argbuf)+1);
    if(newbuf==NULL) printf("no memory");
    strcpy(newbuf,argbuf);
    return newbuf;
}
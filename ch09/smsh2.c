#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include"smsh.h"

#define DFL_PROMPT ">"

void setup();

int main()
{
    char* prompt=DFL_PROMPT;
    setup();
    char* cmdline;
    char* arglist;
    int result;
    while((cmdline=next_cmd(prompt,stdin))!=NULL){
        if((arglist=splitline(cmdline))!=NULL){
            result=process(arglist);
            freelist(arglist);
        }
        free(cmdline);
    }
    return 0;
}

void setup()
{
    signal(SIGINT,SIG_IGN);    //忽略crtl+C信号
    signal(SIGQUIT,SIG_IGN);    //忽略crtl+/信号
}

void fatal(char *s1,char *s2,int n)
{
    fprintf(stderr,"Error: %s,%s \n",s1,s2);
    exit(n);
}
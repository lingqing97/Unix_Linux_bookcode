#include<stdio.h>

#define oops(m,x) { perror(m); exit(x); }

void be_dc(int[],int[]);
void be_bc(int[],int[]);

void fatal(char* mess)
{
    fprintf(stderr,"Error:%s\n",mess);
    exit(1);
}

void main()
{
    int pid,todc[2],fromdc[2];

    //make two pipes
    if(pipe(todc)==-1 || pipe(fromdc)==-1 )
        oops("pipe failed",1);

    //get a process for user interface
    if((pid = fork())==-1)
        oops("cannot fork",2);

    if(pid==0)
        be_dc(todc,fromdc);
    else{
        be_bc(todc,fromdc);
        wait(NULL);
    }
}

void be_dc(int in[2],int out[2])
{
    if(dup2(in[0],0)==-1)
        oops("dc,cannot redirect stdin",3);
    close(in[0]);
    close(in[1]);

    if(dup2(out[1],1)==-1)
        oops("dc,cannot redirect stdout",4);
    close(out[1]);
    close(out[0]);

    execlp("dc","dc","-",NULL);
    oops("cannot run dc",5);
}

void be_bc(int todc[2],int fromdc[2])
{
    int num1,num2;
    char operation[BUFSIZ],message[BUFSIZ];

    close(todc[0]);
    close(fromdc[1]);

    //将管道当成文件操作
    FILE* fpout=fdopen(todc[1],"w");
    FILE* fpin=fdopen(fromdc[0],"r");

    if(fpout==NULL || fpin==NULL)
        fatal("Error convering pipes to streams");

    //main loop
    while(printf("tinybc:"),fgets(message,BUFSIZ,stdin)!=NULL)
    {
        if(sscanf(message,"%d %[- + * /^]%d",&num1,operation,&num2)!=3)
        {
            printf("syntax error\n");
            continue;
        }
        //p是dc计算器的结束标志
        if(fprintf(fpout,"%d\n %d\n %c\np\n",num1,num2,*operation)==EOF)
            fatal("Error writing");
        fflush(fpout);
        if(fgets(message,BUFSIZ,fpin)==NULL)
            break;
        printf("%d %c %d = %s",num1,*operation,num2,message);
    }
    fclose(fpout);
    fclose(fpin);
}
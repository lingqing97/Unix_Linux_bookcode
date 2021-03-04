#include<stdio.h>
#include<pthread.h>
#include<ctype.h>

#define oops(m) { perror(m); exit(1); }

void count_word(void*);

int count=0;
pthread_mutex_t counter_lock=PTHREAD_MUTEX_INITIALIZER;

int main(int ac,char* av[])
{
    if(ac!=3){
        fprintf(stderr,"usage: undefined parameters");
        exit(1);
    }
    pthread_t pid1,pid2;
    pthread_create(&pid1,NULL,count_word,(void*)av[1]);
    pthread_create(&pid2,NULL,count_word,(void*)av[2]);
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);

    printf("Total:%d\n",count);

    return 0;
}

void count_word(void* f)
{
    char* filename=(char*) f;
    FILE* file;
    if((file=fopen(filename,"r"))!=NULL){
        int ch='\0',pre='\0';
        while((ch=getc(file))!=EOF)
        {
            //这个判断有问题!!!
            if(!isalnum(ch)&&isalnum(pre))
                pthread_mutex_lock(&counter_lock);
                ++count;
                pthread_mutex_unlock(&counter_lock);
            pre=ch;
        }
        fclose(file);
    }
    else{
        oops(filename);
    }
}
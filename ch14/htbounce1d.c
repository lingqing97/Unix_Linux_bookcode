#include<stdio.h>
#include<curses.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define MESSAGE "hello"

int row;
int col;
int dir;
int delay;

pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

void main()
{
    int ndelay;
    int c;
    pthread_t msg_thread;
    void* moving_msg();

    initscr();
    crmode();
    noecho();
    clear();

    row=10;
    col=0;
    dir=1;
    delay=200;

    if(pthread_create(&msg_thread,NULL,moving_msg,MESSAGE)){
        fprintf(stderr,"error creating thread");
        endwin();
        exit(0);
    }
    while (1)
    {
        ndelay=0;
        c=getch();
        if(c=='q') break;
        if(c==' '){
            pthread_mutex_lock(&lock);
            dir=-dir;
            pthread_mutex_unlock(&lock);
        }
        if(c=='f' && delay>2) ndelay=delay/2;
        if(c=='s') ndelay=delay*2;
        if(ndelay>0)
            delay=ndelay;
    }
    //Cancels execution of a thread
    pthread_cancel(msg_thread);
    endwin();
}

void* moving_msg(char* msg)
{
    while(1){
        usleep(delay*1000);
        move(row,col);
        addstr(msg);
        refresh();

        col+=dir;

        if(col<=0){
            pthread_mutex_lock(&lock);
            if(dir==-1) dir=1;
            pthread_mutex_unlock(&lock);
        }
        else if(col+strlen(msg)>=COLS)
        {
            pthread_mutex_lock(&lock);
            if(dir==1) dir=-1;
            pthread_mutex_unlock(&lock);
        }
    }
}
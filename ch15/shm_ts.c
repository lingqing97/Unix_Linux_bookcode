#include<stdio.h>
#include<sys/shm.h>
#include<time.h>


#define TIME_MEM_KEY 99         //like a filename
#define SEG_SIZE ((size_t)100)  //size of segment
#define oops(m,x) { perror(m); exit(x); }

void main()
{
    int seg_id=shmget(TIME_MEM_KEY,SEG_SIZE,IPC_CREAT | 077);
    if(seg_id==-1)
        oops("shmget",1);

    char* mem_ptr=shmat(seg_id,NULL,0);

    if(mem_ptr==(void*)-1)
        oops("shmat",2);

    int n;
    long now;
    for(n=0;n<60;++n){
        time(&now);
        strcpy(mem_ptr,ctime(&now));
        sleep(1);
    }
    //now remove it
    shmctl(seg_id,IPC_RMID,NULL);
}
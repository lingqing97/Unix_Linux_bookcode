#include<stdio.h>
#include<sys/shm.h>
#include<time.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#define TIME_MEM_KEY 99
#define TIME_SEM_KEY 9900
#define SEG_SIZE ((size_t)100)
#define oops(m,x) { perror(m); exit(x);}

union semun {int val; struct semid_ds* buf; ushort* array;};

void main()
{
    int seg_id=shmget(TIME_MEM_KEY,SEG_SIZE,0777);
    if(seg_id==-1)
        oops("shmget",1);
    char* mem_ptr=shmat(seg_id,NULL,0);
    if(mem_ptr==(void*)-1)
        oops("shmat",2);

    int semset_id=semget(TIME_SEM_KEY,2,0);
    wait_and_lock(semset_id);

    printf("The time,direct from memory:..%s",mem_ptr);

    release_lock(semset_id);
    shmdt(mem_ptr);     //detach
}

void wait_and_lock(int semset_id)
{
    struct sembuf actions[2];
    //阻塞终止条件
    actions[0].sem_num=1;           //sem[1] is n_writers
    actions[0].sem_flg=SEM_UNDO;    //auto cleanup
    actions[0].sem_op=0;            //wait for 0
    //要执行的动作
    actions[1].sem_num=0;           //sem[0] is n_readers
    actions[1].sem_flg=SEM_UNDO;    //auto cleanup
    actions[1].sem_op=+1;           //incr n_readers

    if(semop(semset_id,actions,2)==-1)
        oops("semop:locking",10);
}

void release_lock(int semset_id)
{
    struct sembuf actions[1];
    actions[0].sem_num=0;
    actions[0].sem_flg=SEM_UNDO;
    actions[0].sem_op=-1;

    if(semop(semset_id,actions,1)==-1)
        oops("semop:unlocking",10);
}
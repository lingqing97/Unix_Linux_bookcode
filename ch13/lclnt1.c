#include<stdio.h>

int validate_ticket();

void do_regular_work()
{
    printf("SuperSleep version 1.0 Running-Licensed Sofware\n");
	sleep(15);	/* our patented sleep algorithm */

	if ( validate_ticket() != 0 && get_ticket() != 0 ){
		printf("Server errors. Please Try later.\n");
		return;
	}
	sleep(15);
}

int main(int ac,char* av[])
{
    setup();
    if(get_ticket()!=0)
        exit(0);
    do_regular_work();

    release_ticket();
    shut_down();
}


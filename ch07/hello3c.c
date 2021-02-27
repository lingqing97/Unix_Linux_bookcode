#include<stdio.h>
#include<curses.h>


#define LEFTEDGE 10
#define RIGHTEDGE 15
#define ROW 10

int main(){
    char* message="hello";
    char* blank  ="     ";
    int dir=+1;
    int pos=LEFTEDGE;

    initscr();
    clear();
    while(1){
        move(ROW,pos);
        addstr(message);
        move(LINES-1,COLS-1);
        refresh();
        sleep(1);
        move(ROW,pos);
        addstr(blank);
        pos+=dir;
        if(pos>=RIGHTEDGE){
            //standout();
            dir=-1;
        }
        if(pos<=LEFTEDGE){
            //standend();
            dir=+1;
        }
    }
}
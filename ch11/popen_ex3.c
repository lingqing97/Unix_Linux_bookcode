#include<stdio.h>

void main()
{
    FILE * fp;
    fp=popen("who|sort","r");
    char buf[100];
    int i=0;
    while(fgets(buf,100,fp)!=NULL)
        printf("%3d %s",i++,buf);
    pclose(fp);
}
#include<stdio.h>
#include<unistd.h>  //for close()
#include<fcntl.h>   //for open()

int main()
{
    char line[100];

    fgets(line,100,stdin); printf("%s\n",line);
    fgets(line,100,stdin); printf("%s\n",line);
    fgets(line,100,stdin); printf("%s\n",line);

    //close(0)-then-open(fd)
    close(0);
    if(open("/etc/passwd",O_RDONLY)==-1)
        perror("open");

    fgets(line,100,stdin); printf("%s\n",line);
    fgets(line,100,stdin); printf("%s\n",line);
    fgets(line,100,stdin); printf("%s\n",line);

    return 0;
}
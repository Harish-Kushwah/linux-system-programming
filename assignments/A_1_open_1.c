/**
    1.Open File
*/

#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main(int argc , char* argv[])
{
    char* fileName = argv[1];

    int fd;

    fd = open(fileName, O_RDONLY);
    

    if(fd<0){
        printf("Error: %s\n",strerror(errno));
        return -1;
    }

    printf("File open successfully with file descriptor: %d\n" , fd);

    close(fd);

    return 0;
}
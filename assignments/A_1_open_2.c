#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>


int getMode(char* mode)
{
     if(strcmp(mode , "R") == 0){
        return O_RDONLY;
    }
    else if(strcmp(mode, "W") == 0){
        return O_WRONLY;
    }
    else if(strcmp(mode, "RW") == 0){
        return O_RDWR;
    }
    else if(strcmp(mode, "A") == 0){
        return O_APPEND | O_CREAT;
    }
    return -1;
}

int main(int argc , char* argv[])
{
    if(argc < 3)
    {
        printf("Please enter filename and mode(R, W, RW, A)\n");
        return -1;
    }

    char* fileName = argv[1];
    int fd = 0;
    int mode = getMode(argv[2]);

    if(mode == -1)
    {
        printf("Please enter valid file mode");
        return -1;
    }

    fd = open(fileName, mode);

    if(fd<0)
    {
        printf("Error: %s\n",strerror(errno));
        return -1;
    }

    printf("File open successfully in %s mode with file descriptor %d\n" , argv[2] , fd);

    close(fd);
    return 0;
}
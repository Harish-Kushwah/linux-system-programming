#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define BUFF_SIZE 1024

int main(int argc, char* argv[])
{
    int fd = 0 , N = 0;
    char* file_name;
    char buff[BUFF_SIZE];

    if (argc != 3) {
        printf("Please enter file name & Number of bytes wants to read(eg. file_name.txt 10)\n");
        return -1;
    }

    file_name = argv[1];
    N = atoi(argv[2]);
    

    fd = open(file_name , O_RDONLY);
    
    if(fd < 0)
    {
        printf("Error: %s\n" , strerror(errno));
        return -1;
    }
    else{
        memset(buff ,'\0',BUFF_SIZE);
        read(fd , &buff , N);
        printf("%s" , buff);
    }

    close(fd);
    return 0;
}
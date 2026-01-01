#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main(int argc , char* argv[])
{
    int fd = 0;

    char* file_path = argv[1];

    fd = access(file_path , O_RDONLY);
    if(fd<0)
    {
        printf("Error: %s\n" ,strerror(errno));
    }
    else
    {
        printf("User has Read permission for the given path %s\n" , file_path);
    }
    return 0;
}
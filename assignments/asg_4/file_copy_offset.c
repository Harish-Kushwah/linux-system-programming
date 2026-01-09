#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc , char* argv[])
{
    int source_fd = 0 , dest_fd = 0;
    char buff[1024];
    int read_bytes = 0;
    int copy_from = 100;  // start copying from 20 

    memset(buff , '\0' , sizeof(buff));

    if(argc < 3)
    {
        printf("Enter both source and destination file names");
        return -1;
    }

    source_fd = open(argv[1] , O_RDONLY);

    if(source_fd<0)
    {
        printf("Error:%s", strerror(errno));
        return -1;
    }

    dest_fd = open(argv[2] , O_WRONLY | O_CREAT , 0777);

    if(dest_fd<0)
    {
        printf("Error:%s", strerror(errno));
        return -1;
    }

    lseek(source_fd , copy_from , SEEK_CUR);

    while((read_bytes = read(source_fd , &buff , sizeof(buff)))>0)
    {
        write(dest_fd , &buff , read_bytes);
    }

    printf("File copped successfully from the offset\n");

    close(source_fd);
    close(dest_fd);
    

    return 0;
}
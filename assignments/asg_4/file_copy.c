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
    
    memset(buff , '\0' , sizeof(buff));


    if(argc < 3)
    {
        printf("Please enter both files names");
        return -1;
    }


    source_fd = open(argv[1] , O_RDONLY);

    if(source_fd < 0)
    {
        printf("Error: %s\n" , strerror(errno));
        return -1;
    }

    dest_fd = open(argv[2] , O_RDWR | O_CREAT | O_APPEND, 0777);

    if(dest_fd < 0)
    {
        printf("Error: %s\n" , strerror(errno));
        return -1;
    }

    while ((read_bytes = read(source_fd , &buff , sizeof(buff)))>0)
    {
        write(dest_fd , &buff , read_bytes);
    }

    printf("%s file copped to %s successfully\n", argv[1], argv[2]);

    close(source_fd);
    close(dest_fd);
    
    return 0;
}
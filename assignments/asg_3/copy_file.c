#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

int main(int argc , char* argv[])
{   
    int source_fd = 0 , dest_fd = 0;
    char buff[1096];
    memset(buff , '\0' , sizeof(buff));
    int bytes_read;

    if(argc < 3)
    {
        printf("Error: Enter both file names");
        return 0;
    }
    source_fd = open(argv[1] , O_RDONLY);

    if(source_fd < 0)
    {
        printf("Error in soruce file : %s\n", strerror(errno));
        return -1;
    }

    dest_fd = open(argv[2] , O_WRONLY | O_CREAT | O_TRUNC , 0777);

    if(dest_fd < 0)
    {
        printf("Error in destination file : %s\n", strerror(errno));
        return -1;
    }

    while ( (bytes_read = read(source_fd , &buff , sizeof(buff))) > 0)
    {
        write(dest_fd,&buff , bytes_read);
    }

    printf("file coppied successfully from %s to %s\n" , argv[1] , argv[2]);

    close(source_fd);
    close(dest_fd);
    
    return 0;
}
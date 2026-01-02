#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>

int main(int argc , char* argv[])
{
    char* file_name = NULL;
    int fd = 0 , iRet;
    struct stat sobj;

    file_name = argv[1];
    fd = open(file_name , O_RDONLY);

    if(fd<0)
    {
        printf("Error: %s\n" , strerror(errno));
        return -1;
    }
    else{

        iRet = stat(file_name, &sobj);

        if(iRet < 0)
        {
            printf("Error: %s\n" , strerror(errno));
            return -1;
        }
        else{
            printf("Inode number : %ld\n",sobj.st_ino);
            printf("Hardlink count : %ld\n",sobj.st_nlink);
            printf("Total size : %ld\n",sobj.st_size);
            printf("Block size : %ld\n",sobj.st_blksize);
        }
    }


    close(fd);
    return -1;
}
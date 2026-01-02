#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc , char* argv[])
{
    int fd = 0;
    int totalBytes = 0;
    int iRet = 0;

    char* fileName = NULL;
    char buff[1024];

    memset(buff , '\0' , sizeof(buff));

    if(argc != 2) 
    {   
        printf("Please enter file name");
        return -1;
    }

    fileName = argv[1];

    fd = open(fileName,O_RDONLY);

    if(fd < 0)
    {
        printf("Error: %s\n" , strerror(errno));
        return -1;
    }

    printf("File content : ");
    while((iRet = read(fd , &buff , sizeof(buff))) && iRet !=0){
        printf("%s" , buff);
        memset(buff , '\0' , sizeof(buff));
        totalBytes += iRet;
    }
    printf("\nTotal bytes read : %d\n" , totalBytes);
    
    close(fd);
    return 0;
}
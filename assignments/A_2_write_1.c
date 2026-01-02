#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

int sizeOfText(char *text)
{
    char* temp = text;
    int iCount = 0;
    while (temp !=NULL && *temp !='\0')
    {
        iCount++;
        temp++;
    }
    return iCount;
}

int main(int argc , char* argv[])
{
    int fd   = 0;
    int iRet = 0;
    char* fileName = NULL; 
    char* text  = NULL;
    int s = 0;

    if(argc < 3)
    {
        printf("Error: Please enter the file name and content to write in the file");
        return -1;
    }

    fileName = argv[1];
    text = argv[2];

    fd = open(fileName , O_WRONLY | O_APPEND);
    if(fd<0)
    {
        printf("Error: %s", strerror(errno));
        return -1;
    }
        
    iRet = write(fd, text ,sizeOfText(text));
    if(iRet < 0)
    {
        printf("Error: %s" , strerror(errno));
        return -1;
    }
    
    printf("Bytes writted into the file: %d\n" , iRet);
    
    close(fd);
    return -1;
}
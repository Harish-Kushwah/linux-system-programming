#include<stdio.h>
#include<dirent.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>

void printMode(int mode_number)
{
    if(S_ISBLK(mode_number))
    {
        printf("Bloced Device\n");
    }
    else if(S_ISCHR(mode_number))
    {
        printf("Character Device\n");
    }
    else if(S_ISDIR(mode_number))
    {
        printf("Directory File\n");
    }
    else if(S_ISREG(mode_number))
    {
        printf("Regular File\n");
    }
    else if(S_ISSOCK(mode_number))
    {
        printf("Socket File\n");
    }
    else if(S_ISFIFO(mode_number))
    {
        printf("Pipe File\n");
    }
    else if(S_ISLNK(mode_number))
    {
        printf("Symbolic Link\n");
    }
}
int main(int argc , char* argv[])
{   
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat stp;
    int iRet = 0;

    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        printf("Error: %s\n" , strerror(errno));
        return -1;
    }

    while (ptr = readdir(dp))
    {
        char* file_name = ptr -> d_name;
        iRet = lstat(file_name , &stp);

        if(iRet < 0){
            printf("Error: %s\n" , strerror(errno));
            return -1;
        }
        printf("%s : " , file_name);
        printMode(stp.st_mode);
    }

    closedir(dp);
    
    return -1;
}
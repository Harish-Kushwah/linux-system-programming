#include<stdio.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>

int main(int argc , char* argv[])
{   
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    int iRet = 0;
    long int maxSize = 0;
    char* maxSizeFileName = NULL;

    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        printf("Error: %s" , strerror(errno));
        return -1;
    }

    while (ptr = readdir(dp))
    {
        char* name = ptr -> d_name;

        iRet = lstat(name , &sobj);

        if(iRet < 0)
        {
            printf("Error: %s" , strerror(errno));
            return -1;
        }

        if(S_ISREG(sobj.st_mode))
        {
            if(sobj.st_size > maxSize ){
                maxSize = sobj.st_size;
                maxSizeFileName = name;
            }
        }
        
    }
        
    printf("Max Size File name : %s \nsize : %ld\n" , maxSizeFileName , maxSize);
    
    closedir(dp);
    return -1;
}
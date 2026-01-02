#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

int main(int argc , char* argv[])
{
    DIR *dp = NULL;

    struct dirent *ptr = NULL;

    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        printf("%s\n" , strerror(errno));
        return -1;
    }

    while (ptr = readdir(dp))
    {
        if(strcmp(ptr -> d_name,".")==0 || strcmp(ptr -> d_name, "..") == 0) continue;
        
        printf("File name: %s\n" , ptr -> d_name);
    }

    closedir(dp);

    return -1;  
}
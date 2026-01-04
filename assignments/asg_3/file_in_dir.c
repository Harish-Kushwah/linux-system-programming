#include<stdio.h>
#include<dirent.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

int main(int argc , char* argv[])
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    char path[4096];

    if(argc < 3)
    {
        printf("Please provide both directory and file name\n");
        return -1;
    }    

    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        printf("Error: %s\n" , strerror(errno));
        return -1;
    }

    while((ptr = readdir(dp)))
    {
        char *name = ptr -> d_name;

        if(strcmp(argv[2] , name)==0)
        {
            printf("file found in given directory\n");

            getcwd(path , sizeof(path));
            
            strcat(path , "/");
            strcat(path , name);

            printf("Absolute path : %s" , path);
        }

    }

    closedir(dp);

    return 0;
}
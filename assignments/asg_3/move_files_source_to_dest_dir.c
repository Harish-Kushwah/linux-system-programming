#include<stdio.h>
#include<dirent.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>

// copy + delete pending
int main(int argc , char* argv[])
{   
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    int iRet = 0;
    char dest_dir[4096];
    char current_path[4096];

    int moved_file_count = 0;

    memset(dest_dir , '\0', sizeof(dest_dir));

    if(argc < 3)
    {
        printf("Enter both source and destination directory name\n");
        return -1;
    }

    strcpy(dest_dir , argv[2]);

    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        printf("Error: %s\n" , strerror(errno));
        return -1;
    }

    while ((ptr = readdir(dp)))
    {
        iRet = lstat(ptr -> d_name , &sobj);
        if(iRet < 0)
        {
            printf("Error: %s\n" , strerror(errno));
            return -1;
        }
        
        if(S_ISREG(sobj.st_mode)){
        
            strcat(dest_dir , "/");
            strcat(dest_dir , ptr -> d_name);
            iRet = rename(ptr -> d_name, dest_dir);
            if(iRet < 0)
            {
                printf("%s\n" , strerror(errno));
                return -1;
            }
            
            moved_file_count++;
            memset(dest_dir , '\0', sizeof(dest_dir));
            strcpy(dest_dir , argv[2]);
        }

    }

    printf("total files moved %d\n" , moved_file_count);

    closedir(dp);

    return 0;
}
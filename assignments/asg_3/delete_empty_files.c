#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

int main(int argc , char* argv[])
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    int iRet = 0;
    int delete_file_count = 0;

    if(argc < 2)
    {
        printf("Please enter directory name\n");
        return -1;
    }

    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }

    while((ptr = readdir(dp)))
    {
        iRet = lstat(ptr->d_name , &sobj);

        if(iRet < 0)
        {
            printf("Please enter directory name\n");
            return -1; 
        }

        if(S_ISREG(sobj.st_mode) && sobj.st_size == 0)
        {   
            iRet =  unlink(ptr -> d_name);
            if(iRet < 0)
            {
                printf("Please enter directory name\n");
                return -1; 
            }

            printf("File Deleted : %s\n",ptr -> d_name);
            delete_file_count ++;

        }
    }

    printf("Toatl files deleted : %d\n" , delete_file_count);
    
    closedir(dp);
    return 0;
}
/**  
 * accept the directory name & rename the file 
 * remove the starting A_X_ from the file name
 * A_1_read_1.c -> read_1.c
*/

#include<stdio.h>
#include<dirent.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include <limits.h>

#define MAX_PATH 4024


int getNameSize(char* name)
{
    char* temp = name;
    int iSize = 0;
    while (temp != NULL && *temp != '\0')
    {
        temp++;
        iSize++;
    }
    return iSize;    
}
int main(int argc , char* argv[])
{
    DIR *dp = NULL;
    char *name = NULL;
    struct dirent *ptr = NULL;

    char destination[1024];

    int iRet = 0;

    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        printf("Error: %s" , strerror(errno));
        return -1;
    }
    
    char cwd[MAX_PATH];
    char newPath[MAX_PATH];

    while (ptr = readdir(dp))
    {
        name = ptr->d_name;

        if(name[0] != 'A')
            continue;
        

        // remove A_2_
        int end = getNameSize(name);
        int start = 4;
        int length = end - start;

        memset(destination,'\0',sizeof(destination)); 
        strncpy(destination, name + start, length);

        memset(cwd, '\0', sizeof(cwd));
        getcwd(cwd , sizeof(cwd));
        strcat(cwd,"/");
        
        strcpy(newPath , cwd);

        printf("cwd %s" , cwd);
        strcat(cwd,name);
        strcat(newPath , destination);
    
        iRet = rename(cwd, newPath);
        if(iRet < 0)
        {
            printf("%s\n" , strerror(errno));
            return -1;
        }
        else{
            printf("file rename successfully\n");
            }
    }
    
    closedir(dp);
    return 0;
}
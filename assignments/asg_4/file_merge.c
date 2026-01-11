#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc, char* argv[])
{
    int target_file_fd = 0;
    int temp_fd = 0;
    char buff[1024] = {'\0'};
    int iRet = 0;

    if(argc < 3)
    {
        printf("Please enter at least 2 file names\n");
        return -1;
    }

    target_file_fd = open(argv[1] , O_WRONLY | O_CREAT | O_APPEND , 0777 );

    if(target_file_fd < 0)
    {
        printf("%s\n" , strerror(errno));
        return -1;
    }

    // read first file and write the content

    for(int i=2; i<argc; i++){
        
        temp_fd = open(argv[i] , O_RDONLY);

        if(temp_fd < 0)
        {
            printf("%s\n" , strerror(errno));
            continue;
        }

        while((iRet = read(temp_fd , &buff , sizeof(buff))) > 0)
        {
            write(target_file_fd , &buff , iRet);
            memset(buff , '\0', sizeof(buff));
        }
        close(temp_fd);
    }

        printf("Filles successfully merged into single file : %s" , argv[1]);

    close(target_file_fd);

    return 0;
}
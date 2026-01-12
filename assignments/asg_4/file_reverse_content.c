#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node
{
    char data[1024];
    struct Node *next;
}Node;

Node* insertAtFirst(Node *head , char *data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    strcpy(newNode->data , data);

    if(head == NULL)
    {
        head = newNode;
    }
    else{
        newNode->next = head;
        head = newNode;
    }
    return head;
}

void printList(Node* head)
{
    for(Node* temp = head; temp != NULL ; temp=temp->next){
        printf("%s" , temp->data);
    }
}
int main(int argc , char* argv[])
{
    int fd = 0;
    int iRet = 0;
    char buff[10] = {'\0'};
    char ans[10] = {'\0'};
    Node* head = NULL;

    char *res = NULL;

    if(argc < 2)
    {
        printf("please provide the file name");
        return -1;
    }
    
    
    fd = open(argv[1] , O_RDONLY);

    if(fd < 0)
    {
        printf("%s\n" , strerror(errno));
        return -1;
    }


    printf("file content in reverse order : \n");
    int total_lines = 0;

    while ((iRet = read(fd , &buff , sizeof(buff)))> 0)
    {
        for(int i=0;i<iRet;i++){

            if(buff[i]=='\n')
            {
                
                head = insertAtFirst(head , ans);
            }
        }
        memset(buff , '\0' , sizeof(buff)); 

    }

    printf("Data from linked list : \n");
    printList(head);

    close(fd);
    
    return 0;
}
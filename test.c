#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include "LList.h"

char load[15];
char buffer[1000];

char convert(char a)
{
    if(a >= 97)
        return a;
    return a+32;
}

int strlenth(char *array)
{
    int i = 0;
    for(int j = 0; j < 10; j ++)
    {
        if(array[j] != ' ')
        {
            i ++;
        }
    }
    return i;
}

void printLList(struct Node *head)
{
    struct Node* current = head;
    char buffer[3];
    while(current != NULL)
    {
        write(STDOUT_FILENO, current->name, 15);
        buffer = sprintf("%i\n", current->count);
        write(STDOUT_FILENO, buffer, 3);
        current = current->next;
    }
}

void readstr(char * array, int length)
{
    for(int j = 0; j < length; j ++)
    {
        printf("%c", array[j]);
    }
    printf("\n");
}

void resetarray(char * array, int length)
{
    for(int i = 0; i < length; i ++)
    {
        array[i] = ' ';
    }
    
}

struct Node* checkExist(struct Node *head, char *name)
{
    struct Node *current = head;
    while(current->next != NULL)
    {
        if(strcmp(current->name, name) == 0)
        {
            current->count ++;
            return head;
        }
        current = current->next;
    }
    struct Node *newNode;
    newNode = LLnode(name, 1, NULL);
    current->next = newNode;
    return head;
}

struct Node* updateList(struct Node *head, char *name)
{
    struct Node *newNode;
    newNode = LLnode(name, 1, NULL);
    if(strcmp(head->name, "!DeFaUt!") == 0)
    {
        head = newNode;
    }
    else
    {
        head = checkExist(head, name);
    }

    return head;
}

int main(int argc, char *argv[])
{
     struct Node *head;
     head = LLnode("!DeFaUt!", 0, NULL);
     resetarray(buffer, 1000);
     resetarray(load, 15);
     int fd = open(argv[1], O_RDONLY);
     read(fd, buffer, 1000);
     int count = 0;
     for(int k = 0; k < 1000; k ++)
     {

        if(buffer[k] != ' ')// right now is not the space
        {
            if((buffer[k] >= 'a' && buffer[k] <= 'z') || (buffer[k] >= 'A' && buffer[k] <= 'Z'))
            {
                if(*(load+count) == ' ')
                {
                    *(load + count) = convert(buffer[k]);
                    count ++;
                 }
            }
        }   
        else// right now is the space,代表要么一个单词结束了， 或者还未开始是前面的空格
        {
            if(*load != ' ')
            {
                head = updateList(head, load);
                resetarray(load, 15);
                count = 0;
            }
        }
     }
     printLList(head);
     close(fd);
     return 0;
}


#include "LList.h"

char load[300];
char buffer[2000000];

char convertToSmall(char a)
{
    if(a >= 97)
        return a;
    return a + 32;
}

void resetarray(char * array, int length)
{
    for(int i = 0; i < length; i ++)
    {
        array[i] = ' ';
    }
}

char* convertToChar(int a, char *buffer)
{
    buffer = (char*)malloc(5*sizeof(char));
    resetarray(buffer,5);
    int copy = a;
    while(a > 0)
    {
        if(a == 0)
        {
            break;
        }
        for(int i = 0; i < 5; i ++)
        {
            if(buffer[i] == ' ')
            {
                buffer[i] = copy % 10 + 48;
                a /= 10;
                copy = a;
                i = 10;
            }
        }
    }

    char *result;
    result = (char*)malloc(5*sizeof(char));
    resetarray(result,5);

    for (int i = 0; i < 5; i++)
    {
        if(buffer[i] == ' ')
        {
            continue;
        }
        result[4-i] = buffer[i];
    }

    int flag = -1;
    for (int i = 0; i < 5; i++)
    {
        if(result[i] == ' ')
        {
            continue;
        }
        else
        {
            if(flag == -1)
            {
                flag = i;
                buffer[i-flag] = result[i];
            }
            else
            {
                buffer[i-flag] = result[i];
            }
        }
     }// buffer now is 200

     return buffer;
}

int strlenth(char *array)
{
    int i = 0;
    for(int j = 0; j < 10; j ++)
    {
        if(array[j] != ' ')
        {
            i ++;
            printf("%c", array[j]);
        }
    }
    return i;
}

void readNode(struct Node *current)
{
    int count = current->count;
    char *buffer;
    char split[] = {'\n'};
    write(STDOUT_FILENO, current->name, 20);
    buffer = convertToChar(current->count, buffer);
    write(STDOUT_FILENO, buffer, sizeof(buffer));
    write(STDOUT_FILENO, split, sizeof(split));

}

void printLList(struct Node *head)
{
    struct Node* current = head;
    while(current != NULL)
    {
        readNode(current);
        current = current->next;
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
    //printf("current name is:%s\n", current->name);
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
     resetarray(buffer, 2000000);
     resetarray(load, 300);
     int fd = open(argv[1], O_RDONLY);
     read(fd, buffer, 2000000);
     int count = 0;
     for(int k = 0; k < 2000000; k ++)
     {

        if(buffer[k] != ' ')// right now is not the space
        {
            if((buffer[k] >= 'a' && buffer[k] <= 'z') || (buffer[k] >= 'A' && buffer[k] <= 'Z'))
            {
                if(*(load+count) == ' ')
                {
                    *(load + count) = convertToSmall(buffer[k]);
                    count ++;
                 }
            }
        }
        else// right now is the space,代表要么一个单词结束了， 或者还未开始是前面的空格
        {
            if(*load != ' ')
            {
                head = updateList(head, load);
                resetarray(load, 300);
                count = 0;
            }
        }
     }
     printLList(head);
     close(fd);
     return 0;
}


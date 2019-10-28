#include "LList.h"

char load[20];
char buffer[600000];

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

int strlenth(char *array)
{
    int i = 0;
    for(int j = 0; j < 5; j ++)
    {
        if(array[j] != ' ')
        {
            i ++;
        }
    }
    return i;
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
     char *r2;
     r2 = (char*)malloc(5*sizeof(char));
     resetarray(r2,5);
     //printf("buffer len is: %i", strlenth(buffer));

     int toleft = 5 - strlenth(buffer);
     
     if(toleft > 0)
     {
        for (int i = 0; i < strlenth(buffer); i++)
        {
            r2[toleft+i] = buffer[i];
        }
     }
     else
     {
        return buffer;
     }
     return r2;
}

void readNode(struct Node *current)
{
    int count = current->count;
    char *buffer;
    char enter[] = {'\n'};
    char is[] = {':'};
    write(STDOUT_FILENO, current->name, 20);
    write(STDOUT_FILENO, is, sizeof(is));
    buffer = convertToChar(current->count, buffer);
    write(STDOUT_FILENO, buffer, 5);
    write(STDOUT_FILENO, enter, sizeof(enter));
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
    if(strcmp(current->name, name) == 0)
    {
        current->count++;
        return head;
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
     resetarray(buffer, 600000);
     resetarray(load, 20);
     int filenum = argc-1;
     while(filenum > 0)
     {
         int fd = open(argv[argc-filenum], O_RDONLY);

         if(fd == -1)
         {
            perror("Error in opening files.!@!@");
            exit(EXIT_FAILURE);
         }
         int read_num = read(fd, buffer, 600000);

         while(read_num != 0)
         {
            int count = 0;

             for(int k = 0; k < 600000; k ++)
             {
                if((buffer[k] >= 'a' && buffer[k] <= 'z') || (buffer[k] >= 'A' && buffer[k] <= 'Z'))// right now is not the space
                {
                    if(load[count] == ' ')
                    {
                        load[count] = convertToSmall(buffer[k]);
                        count ++;
                    }
                }
                else// right now is the space,代表要么一个单词结束了， 或者还未开始是前面的空格
                {
                    if(load[0] != ' ')
                    {
                        head = updateList(head, load);
                        resetarray(load, 20);
                        count = 0;
                    }
                  }
             }
             read_num =read(fd, buffer, 600000);
          }
         resetarray(buffer, 600000);
         filenum --;
         close(fd);
     }
             
    printLList(head);
    printf("argc is: %i\n", argc);
    printf("done\n");
     return 0;
}


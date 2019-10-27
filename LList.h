#include <stdlib.h>

struct Node
{
    char* name;
    int count;
    struct Node* next;
};

struct Node * LLnode(char* name, int count, struct Node* next)
{
    struct Node* newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    char* tmp = (char*)malloc(strlen(name));
    newNode->name = strcpy(tmp, name);
    newNode->count = count;
    newNode->next = next;

    return newNode;
}

char* node_name(struct Node *node)
{
    return node->name;
}

int node_count(struct Node *node)
{
    return node->count;
}

struct Node* node_next(struct Node *node)
{
    return node->next;
}

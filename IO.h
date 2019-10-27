#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <LList.c>

struct *node head;
struct *node last;
char buffer[100];

void print_name(Node *node)
{
    puts(node->name);
    getch();
}

void print_count(Node *node)
{
    puts(node->count);

}

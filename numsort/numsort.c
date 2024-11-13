#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

// loads data from a file to a linked list and attaches into a pointer
node *load(char *file_source);

// writes any kind of linked list to a specified file source
void write(node *linked_list, char *file_source);

// unloads all variables that is allocated
void unload(node *linked_list);

// compares and swaps unordered variables
void sort(node *linked_list);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./revision FILE OUTPUTFILE \n");
        return 1;
    }
    node *face = load(argv[1]);
    sort(face);
    write(face, argv[2]);
    unload(face);
}

// loads data from a file to a linked list and attaches into a pointer
node *load(char *file_source)
{
    FILE *file = fopen(file_source, "r");
    if (file == NULL)
    {
        return NULL;
    }
    int tmp = 0;
    node *head = NULL;
    int i = 0;
    // creation of a new node
    while (fscanf(file, "%i", &tmp) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return NULL;
        }
        n->number = tmp;
        n->next = head;
        head = n;
    }
    fclose(file);
    return head;
}

// writes any kind of linked list to a specified file source
void write(node *linked_list, char *file_source)
{
    FILE *file = fopen(file_source, "w");
    if (file == NULL)
    {
        printf("Failed to create file \" %s \" ", file_source);
        return;
    }
    node *ptr = linked_list;
    while (ptr != NULL)
    {
        fprintf(file, "%d\n", ptr->number);
        ptr = ptr->next;
    }
    ptr = NULL;
    fclose(file);
    return;
}

// unloads all variables that is allocated
void unload(node *linked_list)
{
    node *ptr = linked_list;
    while (ptr != NULL)
    {
        ptr = ptr->next;
        free(linked_list);
        linked_list = ptr;
    }
    ptr = NULL;
}

// compares and swaps unordered variables
void sort(node *linked_list)
{
    node *ptr = linked_list;
    while (ptr->next != NULL)
    {
        if (ptr->number > ptr->next->number)
        {
            int temp = ptr->number;
            ptr->number = ptr->next->number;
            ptr->next->number = temp;
        }
        ptr = ptr->next;
    }
}

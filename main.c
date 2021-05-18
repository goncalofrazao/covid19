#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "input.h"


void printlist(fix_t *head)
{

    while (head != NULL)
    {
        printf("%s -- %lu\n", head->name, head->population);
        
        head = head->next;
    }
    printf("\n");
}


int main(int argc, char **argv)
{
    fix_t *head;
    char *what_to_read = (char*) malloc(strlen(argv[1]) * sizeof(char));
    strcpy(what_to_read, argv[1]);
    head = read_input(what_to_read);
    output(head);
    return 0;
}
/*
    fix_t *head;
    head = read_input();

    alphabetical(&head);   
    printlist(head);

    printf("\n");
*/
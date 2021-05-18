#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "input.h"
#include "order_data.h"

int main(int argc, char **argv)
{
    fix_t *head;
    char what_to_read[20];
    strcpy(what_to_read, argv[1]);
    head = read_input(what_to_read);
    head = pop_order(head);
    output(head);
    return 0;
}
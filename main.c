#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "input.h"
#include "order_data.h"
#include "select_data.h"
#include "restrict_data.h"

int main(int argc, char **argv)
{
    fix_t *head;
    fix_t *aux1;
    int year = atoi(argv[2]);
    int week = atoi(argv[3]);
    char what_to_read[20];
    strcpy(what_to_read, argv[1]);
    head = read_input(what_to_read);
    
    head = max_pop(head, 100);
    /*
    aux1 = head;
    while(aux1 != NULL){
        ratiodea_select(aux1);
        aux1 = aux1->next;
    }
    */
    _op(head);
    return 0;
}

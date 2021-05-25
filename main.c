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
    int n = 1;
    int year;
    int week;
    char what_to_read[20];
    char filename_input[20];
    strcpy(filename_input, argv[2]);
    char filename_output[20];
    strcpy(filename_output, argv[3]);
    strcpy(what_to_read, argv[1]);
    printf("go input\n");
    head = read_input(what_to_read, filename_input);
    //head = binary_input(filename_input);
    printf("read input\n");
    restrict_weeks(head, 1, 2020, 20, 2020);
    /*
    while(aux != NULL){
        ratiodea_select(aux);
        aux = aux->next;
    }
    */
    printf("go output\n");
    output(head, filename_output);
    //binary_output(head, filename_output);
    printf("generate output\n");
    return 0;
}

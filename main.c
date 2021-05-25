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
    head = binary_input(filename_input);
    //restrict_weeks(head, 10, 2020, 15, 2020);

    output(head, filename_output);
    return 0;
}

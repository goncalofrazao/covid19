#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "input.h"
#include "order_data.h"
#include "select_data.h"
#include "restrict_data.h"
#include "console.h"

int main(int argc, char **argv)
{
    fix_t *head = NULL;
    fix_t *aux1;
    int n = 0;
    int year = 0;
    int week = 0;
    int max_year = 0;
    int max_week = 0;
    int read_binary = 0;
    int write_binary = 0;
    if(argc < 5){
        console_error();
    }
    char *what_to_read = get_L(argc, argv);
    char *filename_input = get_input_file_name(argc, argv);
    char *filename_output = get_ouput_file_name(argc, argv);
    char *order = get_S(argc, argv, &year, &week);
    char *select = get_D(argc, argv);
    char *restrictor = get_P(argc, argv, &n, &year, &week, &max_year, &max_week);
    if(filename_input == NULL || filename_output == NULL)
        console_error();
    if(what_to_read == NULL){
        what_to_read = (char*) malloc(sizeof(char) * 4);
        strcpy(what_to_read, "all");
    }
    if(order == NULL){
        order = (char*) malloc(sizeof(char) * 5);
        strcpy(order, "alfa");
    }
    if (filename_input[strlen(filename_input) - 1] == 't')
        read_binary = 1;
    if (filename_output[strlen(filename_output) - 1] == 't')
        write_binary = 1;
    if(read_binary)
        binary_input(filename_input);
    else
        read_input(what_to_read, filename_input);
    
    if(strcmp(order, "alfa") == 0)
        head = alpha_order(head);
    else if(strcmp(order, "pop") == 0)
        head = pop_order(head);
    else if(strcmp(order, "inf") == 0)
        head = inf_order(head, year, week);
    else if(strcmp(order, "dea") == 0)
        head = dea_order(head, year, week);

    if(strcmp(select, "inf") == 0){
        aux1 = head;
        while(aux1 != NULL){
            inf_select(aux1);
            aux1 = aux1->next;
        }
    }
    else if(strcmp(select, "dea") == 0){
        aux1 = head;
        while(aux1 != NULL){
            dea_select(aux1);
            aux1 = aux1->next;
        }
    }
    else if(strcmp(select, "racioinf") == 0){
        aux1 = head;
        while(aux1 != NULL){
            ratioinf_select(aux1);
            aux1 = aux1->next;
        }
    }
    else if(strcmp(select, "raciodea") == 0){
        aux1 = head;
        while(aux1 != NULL){
            ratiodea_select(aux1);
            aux1 = aux1->next;
        }
    }

    printf("test\n");
    if(strcmp(restrictor, "min") == 0)
        head = min_pop(head, n);
    else if(strcmp(restrictor, "max") == 0)
        head = max_pop(head, n);
    else if(strcmp(restrictor, "date") == 0)
        restrict_week(head, week, year);
    else if(strcmp(restrictor, "dates") == 0)
        restrict_weeks(head, week, year, max_week, max_year);

    if(write_binary)
        binary_output(head, filename_output);
    else
        output(head, filename_output);


    return 0;
}

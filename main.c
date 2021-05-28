/*******************************************************************************
*  2º Semestre do 1º ano do curso de MEEC - Instituto Superior Técnico
*  Unidade Curricular - Programação
*
*  Nome do Projeto: Pandemia
*
*  Autores: Gonçalo Frazão (99945) e João Mateus (99969)
*  Data de fim: 28/05/2021
*******************************************************************************/

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
    int flag = 0;
    int n = 0;
    int year = 0;
    int week = 0;
    int year1 = 0;
    int week1 = 0;
    int year2 = 0;
    int week2 = 0;
    int read_binary = 0;
    int write_binary = 0;
    // check input minimums
    if(argc < 5){
        console_error();
    }
    // get console input
    char *what_to_read = get_L(argc, argv);
    char *filename_input = get_input_file_name(argc, argv);
    char *filename_output = get_ouput_file_name(argc, argv);
    order_data order = get_S(argc, argv, &year, &week);
    select_data select = get_D(argc, argv);
    restrict_data restrictor = get_P(argc, argv, &n, &year1, &week1, &year2, &week2);
    // if what_to_read has no input, put it the dafault value (all)
    if(what_to_read == NULL){
        what_to_read = (char*) malloc(sizeof(char) * 4);
        strcpy(what_to_read, "all");
        flag = 1;
    }
    // check if input and ouput are binary files
    if (filename_input[strlen(filename_input) - 1] == 't')
        read_binary = 1;
    if (filename_output[strlen(filename_output) - 1] == 't')
        write_binary = 1;
    
    // read input file
    if(read_binary)
        head = binary_input(filename_input);
    else
        head = read_input(what_to_read, filename_input);

    // select data
    if(select == SELECT_INF){
        aux1 = head;
        while(aux1 != NULL){
            inf_select(aux1);
            aux1 = aux1->next;
        }
    }
    else if(select == SELECT_DEA){
        aux1 = head;
        while(aux1 != NULL){
            dea_select(aux1);
            aux1 = aux1->next;
        }
    }
    else if(select == RACIOINF){
        aux1 = head;
        while(aux1 != NULL){
            ratioinf_select(aux1);
            aux1 = aux1->next;
        }
    }
    else if(select == RACIODEA){
        aux1 = head;
        while(aux1 != NULL){
            ratiodea_select(aux1);
            aux1 = aux1->next;
        }
    }
    // restrict data
    if(restrictor == MIN)
        head = min_pop(head, n);
    else if(restrictor == MAX)
        head = max_pop(head, n);
    else if(restrictor == DATE)
        restrict_weeks(head, week1, year1, week1, year1);
    else if(restrictor == DATES)
        restrict_weeks(head, week1, year1, week2, year2);

    // order data
    if(order == ALFA)
        head = alpha_order(head);
    else if(order == POP)
        head = pop_order(head);
    else if(order == INF)
        head = inf_order(head, year, week);
    else if(order == DEA)
        head = dea_order(head, year, week);

    // generate binary
    if(write_binary)
        binary_output(head, filename_output);
    else
        output(head, filename_output);

    // free what_to_read if memory has been allocated   
    if(flag == 1)
        free(what_to_read);
    
    return 0;
}

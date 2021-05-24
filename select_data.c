#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "select_data.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: inf_select
 * 
 * Arguments: fix_t *country -- pointer to the country to select the
 *                              week with most cases.
 * 
 * Return: no return
 * 
 * Description: This function puts in the head of a country the week 
 *              with the most cases and libert all memory allocated
 *              for other weeks.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void inf_select(fix_t *country)
{
    var_t list_head;
    list_head.next = country->var;
    var_t *saver = &list_head;
    var_t *aux1 = saver->next;
    // find the week with most cases
    if(aux1->next != NULL){
        while(aux1->next != NULL){
            if(aux1->next->weekly_cases > saver->next->weekly_cases){
                saver = aux1;
            }
            aux1 = aux1->next;
        }
        //printf("%d-%d\n", saver->next->year, saver->next->week);
        // put the week with most cases in head of the list of dates
        //print_secondary(country->var);
        country->var = put_in_head(saver, country->var);
        // free all other dates
        free_list(country->var->next);
        country->var->next = NULL;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: put_in_head
 * 
 * Arguments: var_t *aux1 -- pointer to the element of the list before
 *                           the week to put in head
 * 
 * Return: aux2 -- the pointer to the new head
 * 
 * Description: This function removes the next struct of input and puts
 *              it in head
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

var_t *put_in_head(var_t *to_put, var_t *head)
{
    var_t *aux1 = to_put->next;
    if (aux1 != head){
        // remove element of the list
        to_put->next = to_put->next->next;
        aux1->next = head;
    }
    return aux1;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: free_list
 * 
 * Arguments: var_t *aux1 -- pointer to the first element of the list
 *                           to libert.
 * 
 * Return: no return
 * 
 * Description: This function liberts fully a list
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void free_list(var_t *to_free)
{

    var_t *aux1;
    while(to_free != NULL){
        aux1 = to_free->next;
        free(to_free);
        printf("%d-%d --- %d-%d\n", to_free->year, to_free->week, to_free->next->year, to_free->next->week);
        to_free = aux1;
    }
}

void print_secondary(var_t *head)
{
    while(head != NULL){
        printf("%d-%d\n", head->year, head->week);
        head = head->next;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: dea_select
 * 
 * Arguments: fix_t *country -- pointer to the country to select the
 *                              week with most deaths.
 * 
 * Return: no return
 * 
 * Description: This function puts in the head of a country the week 
 *              with the most deaths and libert all memory allocated
 *              for other weeks.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void dea_select(fix_t *country)
{
    var_t list_head;
    list_head.next = country->var;
    var_t *aux1 = country->var;
    var_t *saver = &list_head;
    // find the week with most cases
    if(aux1->next != NULL){
        while(aux1->next != NULL){
            if(aux1->next->weekly_deaths > saver->next->weekly_deaths){
                saver = aux1;
            }
            aux1 = aux1->next;
        }
        // put the week with most cases in head of the list of dates
        country->var = put_in_head(saver, country->var);
        // free all other dates
        free_list(country->var->next);
        country->var->next = NULL;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: ratioinf_select
 * 
 * Arguments: fix_t *country -- pointer to the country to select the
 *                              week with most deaths.
 * 
 * Return: no return
 * 
 * Description: This function puts in the head of a country the week 
 *              with the most ratio of infected and libert all memory
 *              allocated for other weeks.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void ratioinf_select(fix_t *country)
{
    var_t list_head;
    list_head.next = country->var;
    var_t *aux1 = country->var;
    var_t *saver = &list_head;
    // find the week with most cases
    if(aux1->next != NULL){
        while(aux1->next != NULL){
            if(aux1->next->rate_cases > saver->next->rate_cases){
                saver = aux1;
            }
            aux1 = aux1->next;
        }
        // put the week with most cases in head of the list of dates
        country->var = put_in_head(saver, country->var);
        // free all other dates
        free_list(country->var->next);
        country->var->next = NULL;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: ratiodea_select
 * 
 * Arguments: fix_t *country -- pointer to the country to select the
 *                              week with most deaths.
 * 
 * Return: no return
 * 
 * Description: This function puts in the head of a country the week 
 *              with the most ratio of deaths and libert all memory
 *              allocated for other weeks.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void ratiodea_select(fix_t *country)
{
    var_t list_head;
    list_head.next = country->var;
    var_t *aux1 = country->var;
    var_t *saver = &list_head;
    // find the week with most cases
    if(aux1->next != NULL){
        while(aux1->next != NULL){
            if(aux1->next->rate_deaths > saver->next->rate_deaths){
                saver = aux1;
            }
            aux1 = aux1->next;
        }
        // put the week with most cases in head of the list of dates
        country->var = put_in_head(saver, country->var);
        // free all other dates
        free_list(country->var->next);
        country->var->next = NULL;
    }
}